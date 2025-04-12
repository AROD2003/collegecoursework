import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

public class ContactServiceTest {
    private ContactService service;
    private Contact contact1;
    private Contact contact2;

    @Before
    public void setUp() {
        service = new ContactService();
        contact1 = new Contact("1", "John", "Doe", "0123456789", "123 Main St");
        contact2 = new Contact("2", "Jane", "Smith", "0987654321", "456 Elm St");
    }

    @Test
    public void testAddContactSuccess() {
        service.addContact(contact1);
        service.addContact(contact2);
    }

    @Test(expected = IllegalArgumentException.class)
    public void testAddContactDuplicateId() {
        service.addContact(contact1);
        Contact duplicateContact = new Contact("1", "Jim", "Beam", "1112223333", "789 Oak St");
        service.addContact(duplicateContact);
    }

    @Test
    public void testDeleteContactSuccess() {
        service.addContact(contact1);
        service.deleteContact("1");
        assertFalse(service.contacts.containsKey("1"));
    }

    @Test(expected = IllegalArgumentException.class)
    public void testDeleteContactNonexistentId() {
        service.deleteContact("nonexistent");
    }

    @Test
    public void testUpdateFirstNameSuccess() {
        service.addContact(contact1);
        service.updateFirstName("1", "Johnny");
        assertEquals("Johnny", contact1.getFirstName());
    }

    @Test(expected = IllegalArgumentException.class)
    public void testUpdateFirstNameNonexistentId() {
        service.updateFirstName("nonexistent", "Johnny");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testUpdatePhoneInvalidNumber() {
        service.addContact(contact1);
        service.updatePhone("1", "123");
    }
}
