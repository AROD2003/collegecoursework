import java.util.HashMap;
import java.util.Map;

public class ContactService {
    private final Map<String, Contact> contacts = new HashMap<>();

    public boolean addContact(Contact contact) {
        if (contacts.containsKey(contact.contactId)) {
            return false;
        }
        contacts.put(contact.contactId, contact);
        return true;
    }

    public boolean deleteContact(String contactId) {
        return contacts.remove(contactId) != null;
    }

    public boolean updateContact(String contactId, String firstName, String lastName, String phoneNumber, String address) {
        Contact contact = contacts.get(contactId);
        if (contact == null) {
            return false;
        }
        if (firstName != null && !firstName.isEmpty()) {
            contact.firstName = firstName;
        }
        if (lastName != null && !lastName.isEmpty()) {
            contact.lastName = lastName;
        }
        if (phoneNumber != null && !phoneNumber.isEmpty()) {
            contact.phoneNumber = phoneNumber;
        }
        if (address != null && !address.isEmpty()) {
            contact.address = address;
        }
        return true;
    }

    public Contact getContact(String contactId) {
        return contacts.get(contactId);
    }
}
