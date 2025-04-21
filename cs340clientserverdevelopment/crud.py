from pymongo import MongoClient
from pymongo.errors import PyMongoError

class AnimalShelter:
    def __init__(self, username, password):
        try:
            self.client = MongoClient(
                f'mongodb://{username}:{password}@nv-desktop-services.apporto.com:30571/?authSource=admin'
            )
            self.database = self.client['AAC']
        except PyMongoError as e:
            print(f"Error connecting to MongoDB: {e}")
            raise


    def create(self, data, collection):
        try:
            result = self.database[collection].insert_one(data)
            return True if result.acknowledged else False
        except PyMongoError as e:
            print(f"Create error: {e}")
            return False

    def read(self, query, collection):
        try:
            results = list(self.database[collection].find(query))
            return results
        except PyMongoError as e:
            print(f"Read error: {e}")
            return []

    def update(self, query, update_data, collection):
        try:
            result = self.database[collection].update_many(query, {'$set': update_data})
            return result.modified_count
        except PyMongoError as e:
            print(f"Update error: {e}")
            return 0

    def delete(self, query, collection):
        try:
            result = self.database[collection].delete_many(query)
            return result.deleted_count
        except PyMongoError as e:
            print(f"Delete error: {e}")
            return 0