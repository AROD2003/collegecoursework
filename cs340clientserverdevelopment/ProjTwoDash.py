from jupyter_dash import JupyterDash
import dash_leaflet as dl
from dash import dcc, html, dash_table
from dash.dependencies import Input, Output
import base64
import pandas as pd
import plotly.express as px

from crud import AnimalShelter

# set credentials and collection
username = "aacuser"
password = "newPassword123"
collection = "animals"
db = AnimalShelter(username, password)

# initial data load
df = pd.DataFrame.from_records(db.read({}, collection))
df.drop(columns=['_id'], inplace=True)

# encode logo
image_filename = 'Grazioso Salvare Logo.png'
encoded_image = base64.b64encode(open(image_filename, 'rb').read())

# app setup
app = JupyterDash(__name__)
app.layout = html.Div([
    html.Img(src='data:image/png;base64,{}'.format(encoded_image.decode()), style={'width': '200px'}),
    html.H1("Grazioso Salvare - Rescue Dashboard", style={'textAlign': 'center'}),
    html.H4("Created by Aaron Rodriguez", style={'textAlign': 'center'}),
    html.Hr(),

    dcc.RadioItems(
        id='filter-type',
        options=[
            {'label': 'Water Rescue', 'value': 'Water Rescue'},
            {'label': 'Mountain or Wilderness Rescue', 'value': 'Mountain or Wilderness Rescue'},
            {'label': 'Disaster or Individual Tracking', 'value': 'Disaster or Individual Tracking'},
            {'label': 'Reset', 'value': 'Reset'}
        ],
        value='Reset',
        labelStyle={'display': 'inline-block'}
    ),
    html.Hr(),

    dash_table.DataTable(
        id='datatable-id',
        columns=[{"name": i, "id": i, "deletable": False, "selectable": True} for i in df.columns],
        data=df.to_dict('records'),
        page_size=10,
        style_table={'overflowX': 'auto'},
        style_cell={'textAlign': 'left'},
        row_selectable='single'
    ),
    html.Br(),
    html.Hr(),

    html.Div(className='row', style={'display': 'flex'}, children=[
        html.Div(id='graph-id', className='col s12 m6'),
        html.Div(id='map-id', className='col s12 m6')
    ])
])

# filtering callback
@app.callback(Output('datatable-id', 'data'), [Input('filter-type', 'value')])
def update_dashboard(filter_type):
    rescue_breeds = {
        "Water Rescue": ["Labrador Retriever", "Chesapeake Bay Retriever", "Newfoundland"],
        "Mountain or Wilderness Rescue": ["German Shepherd", "Alaskan Malamute", "Border Collie"],
        "Disaster or Individual Tracking": ["Bloodhound", "Bluetick Coonhound", "Black and Tan Coonhound"]
    }

    if filter_type == 'Reset':
        dff = pd.DataFrame.from_records(db.read({}, collection))
    else:
        dff = pd.DataFrame.from_records(db.read({"breed": {"$in": rescue_breeds[filter_type]}}, collection))

    dff.drop(columns=['_id'], inplace=True)
    return dff.to_dict('records')

# pie chart update
@app.callback(Output('graph-id', "children"), [Input('datatable-id', "derived_virtual_data")])
def update_graphs(viewData):
    if viewData is None or len(viewData) == 0:
        return []
    dff = pd.DataFrame.from_dict(viewData)
    fig = px.pie(dff, names='breed', title='Breed Distribution')
    return [dcc.Graph(figure=fig)]

# style update for column highlighting
@app.callback(Output('datatable-id', 'style_data_conditional'), [Input('datatable-id', 'selected_columns')])
def update_styles(selected_columns):
    return [{'if': {'column_id': i}, 'background_color': '#D2F3FF'} for i in selected_columns or []]

# map update
@app.callback(Output('map-id', "children"),
              [Input('datatable-id', "derived_virtual_data"),
               Input('datatable-id', "derived_virtual_selected_rows")])
def update_map(viewData, index):
    if viewData is None or index is None:
        return []
    dff = pd.DataFrame.from_dict(viewData)
    row = index[0] if index else 0

    return [
        dl.Map(style={'width': '1000px', 'height': '500px'}, center=[30.75, -97.48], zoom=10, children=[
            dl.TileLayer(id="base-layer-id"),
            dl.Marker(position=[dff.iloc[row]['location_lat'], dff.iloc[row]['location_long']], children=[
                dl.Tooltip(dff.iloc[row]['breed']),
                dl.Popup([
                    html.H1("Animal Name"),
                    html.P(dff.iloc[row]['name'])
                ])
            ])
        ])
    ]

app.run_server(mode='inline')
