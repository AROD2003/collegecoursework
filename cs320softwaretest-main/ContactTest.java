import static org.junit.Assert.*;
import org.junit.Test;

public class ContactTest {

    @Test
    public void testContactCreationSuccess() {
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        assertEquals("1234567890", contact.getContactId());
        assertEquals("John", contact.getFirstName());
        assertEquals("Doe", contact.getLastName());
        assertEquals("0123456789", contact.getPhone());
        assertEquals("123 Main St", contact.getAddress());
    }

    @Test(expected = IllegalArgumentException.class)
    public void testContactIdNull() {
        new Contact(null, "John", "Doe", "0123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testContactIdTooLong() {
        new Contact("12345678901", "John", "Doe", "0123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testFirstNameNull() {
        new Contact("1234567890", null, "Doe", "0123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testFirstNameTooLong() {
        new Contact("1234567890", "Johnathanathan", "Doe", "0123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testLastNameNull() {
        new Contact("1234567890", "John", null, "0123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testLastNameTooLong() {
        new Contact("1234567890", "John", "Doedoe-doe", "0123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testPhoneNull() {
        new Contact("1234567890", "John", "Doe", null, "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testPhoneInvalidLength() {
        new Contact("1234567890", "John", "Doe", "123456789", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testPhoneNonNumeric() {
        new Contact("1234567890", "John", "Doe", "abcdefghij", "123 Main St");
    }

    @Test(expected = IllegalArgumentException.class)
    public void testAddressNull() {
        new Contact("1234567890", "John", "Doe", "0123456789", null);
    }

    @Test(expected = IllegalArgumentException.class)
    public void testAddressTooLong() {
        new Contact("1234567890", "John", "Doe", "0123456789", "1234567890123456789012345678901");
    }

    @Test
    public void testSetFirstNameSuccess() {
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        contact.setFirstName("Jane");
        assertEquals("Jane", contact.getFirstName());
    }

    @Test(expected = IllegalArgumentException.class)
    public void testSetFirstNameNull() {
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        contact.setFirstName(null);
    }

    @Test(expected = IllegalArgumentException.class)
    public void testSetFirstNameTooLong() {
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        contact.setFirstName("Johnathanathan");
    }

}
