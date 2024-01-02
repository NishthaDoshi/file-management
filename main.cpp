#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int BLOCK_SIZE = 10;
vector<int> disk(1000, -1);  // Represents the disk blocks as a linked list

struct inode {
    int id;
    string name;
    int size;
    string permissions;
    string creationdate;
    vector<int> data_blocks;  // Representing the data blocks using a list
};

map<int, inode> masternode;

void Insertion_of_data(int id, string name, int size, string permissions, string creationdate) {
    inode inode_sample;
    inode_sample.id = id;
    inode_sample.name = name;
    inode_sample.size = size;
    inode_sample.permissions = permissions;
    inode_sample.creationdate = creationdate;
    cout << "File created Sucessfully!\n";
    int current_block = 0;
    int remaining_size = size;
    while (remaining_size > 0) {
        for (int i = 0; i < disk.size(); ++i) {
            if (disk[i] == -1) {  // Find an empty block
                disk[i] = (i == disk.size() - 1) ? -1 : i + 1;  // Set next block for the current block
                inode_sample.data_blocks.push_back(i);  // Store block index in i-node
                current_block = i;
                break;
            }
        }
        int write_size = min(remaining_size, BLOCK_SIZE);
        // Simulated write to disk
        remaining_size -= write_size;
    }

    masternode[id] = inode_sample;
}

void Retrieve_data(int id) {
    if (masternode.find(id) == masternode.end()) {
        cout << "ERROR: File with ID " << id << " does not exist.\n";
    } else {
        inode samplet = masternode[id];
        cout << "File ID: " << samplet.id << endl;
        cout << "File Name: " << samplet.name << endl;
        cout << "File Size (in MB): " << samplet.size << endl;
        cout << "Allowed Permissions: " << samplet.permissions << endl;
        cout << "File Creation Date: " << samplet.creationdate << endl;
    }
}

void Update_data(int id) {
    if (masternode.find(id) == masternode.end()) {
        cout << "Error: File having entered ID does not exist.\n";
    } else {
        inode updatedfile = masternode[id];
        int choice;

        do {
            cout << "Select the data you want to update:\n";
            cout << "1. File name\n";
            cout << "2. File size\n";
            cout << "3. File permissions\n";
            cout << "4. File creation date\n";
            cout << "5. Done updating\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name;
                    cout << "Enter new file name: ";
                    cin >> name;
                    updatedfile.name = name;
                    break;
                }
                case 2: {
                    int size;
                    cout << "Enter new file size (in MB): ";
                    cin >> size;
                    updatedfile.size = size;
                    break;
                }
                case 3: {
                    string permissions;
                    cout << "Enter new file permissions: ";
                    cin >> permissions;
                    updatedfile.permissions = permissions;
                    break;
                }
                case 4: {
                    string creationdate;
                    cout << "Enter new file creation date: ";
                    cin >> creationdate;
                    updatedfile.creationdate = creationdate;
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);

        masternode[id] = updatedfile; // Update the inode in the map
    }
}


void DeleteData(int id) {
    if (masternode.find(id) == masternode.end()) {
        cout << "Error: File having entered ID does not exist.\n";
    } else {
        // Simulate deleting blocks from disk
        for (int block : masternode[id].data_blocks) {
            disk[block] = -1;  // Mark blocks as empty
        }
        masternode.erase(id); // Remove the i-node from the map
        cout << "File with ID " << id << " has been deleted.\n";
    }
}

int main() {
    int choice=0;
    while ((choice!=5))
    {
        cout << "Please Enter The Number Accordingly !\n";
        cout << "1. to create a new file.\n";
        cout << "2. to retrieve your data.\n";
        cout << "3. to update your data.\n";
        cout << "4. to delete your file.\n";
        cout << "5. to exit.\n";
        cin >> choice;

        switch (choice)
        {
        case 1:{
            int id,size;
            string name, permissions, creationdate;

            cout << "Enter file ID: ";
            cin >> id;

        if (masternode.find(id) != masternode.end()) {
        cout << "Error: An i-node with ID " << id << " already exists.\n";
        continue;
        }

            cout << "Enter file name: ";
            cin >> name;
            cout << "Enter file size (in MB): ";
            cin >> size;
            cout << "Enter file permissios: ";
            cin >> permissions;
            cout << "Enter file creation date: ";
            cin >> creationdate;

            //calling the function to store this data
            Insertion_of_data(id, name, size, permissions, creationdate);

        }
        break;

        case 2:{
            int id;
            cout << "Enter the ID of the file to retrieve: ";
            cin >> id;
            Retrieve_data(id); //calling the function to retrieve the data
            
        }
        break;

        case 3:{
            int id;
            cout << "Enter the ID of the file to update: ";
            cin >> id;
            // Calling the function to update the data
            Update_data(id);
        }
        break;

        case 4:{
            int id;
            cout << "Enter the ID of the file to delete: ";
            cin >> id;
            // Callin a function to delete the data
            DeleteData(id);
        }
        break;
        
        default:
            break;
        }
    }
    
    return 0;
}
