#include <bits/stdc++.h>
using namespace std;

class super_block
{
public:
    // int bit_block[1000];
    int bit_block[131072];
    int num_of_blocks;
    int size_block;
    int num_of_inode;
    // int bit_inode[200];
    int bit_inode[78644];
};

map<string, int> file_to_descriptor;
class inode
{
public:
    int size;
    int first_block;
    char name[20];
    int last_block;
    int mode;
};

class block
{
public:
    int next_block;
    // char data[512];
    char data[4096];
};

super_block sb;
inode *inodes;
block *blocks;
int create_disk(string str)
{
    FILE *file;
    size_t test;
    int closeVal;
    // sb.num_of_inode = 200;
    sb.num_of_inode = 78644;
    // sb.num_of_blocks = 1000;
    sb.size_block = sizeof(struct block);
    sb.num_of_blocks = 131072;

    int i = 0;
    inodes = (inode *)malloc(sizeof(struct inode) * sb.num_of_inode);
    for (; i < sb.num_of_inode;)
    {
        string nn = "NA";
        inodes[i].first_block = -1;
        sb.bit_inode[i] = -1;
        inodes[i].last_block = -1;
        inodes[i].size = -1;
        strcpy(inodes[i].name, nn.c_str());
        inodes[i].mode = -1;
        i += 1;
    }
    blocks = (block *)malloc(sizeof(struct block) * sb.num_of_blocks);
    i = 0;
    for (; i < sb.num_of_blocks;)
    {
        blocks[i].next_block = -1;
        sb.bit_block[i] = -1;
        string nn = "";
        i += 1;
        strcpy(blocks[i].data, nn.c_str());
    }

    file = fopen(str.c_str(), "w+");
    test = fwrite(&sb, sizeof(struct super_block), 1, file);
    test = fwrite(inodes, sizeof(struct inode) * sb.num_of_inode, 1, file);
    test = fwrite(blocks, sizeof(struct block) * sb.num_of_blocks, 1, file);
    closeVal = fclose(file);
    return 0;
}



int find_empty_inode()
{
    int i = 0;
    while (i < sb.num_of_inode)
    {
        if (sb.bit_inode[i] == -1)
        {
            return i;
        }
        else
        {
            ;
            // do nothing
        }
        i++;
    }
    return -1;
}


int find_empty_block()
{
    int i = 0, returnVal = -1;
    while (i < sb.num_of_blocks)
    {
        if (sb.bit_block[i] == -1)
        {
            return i;
        }
        else
        {
            ;
            // do nothing
        }
        i++;
    }
    return returnVal;
}

int create_file(string name)
{
    int error = 0, in, use_inode = 1;
    in = find_empty_inode();
    if (error)
    {
        printf("error while creating file");
    }
    sb.bit_inode[in] = use_inode;
    strcpy(inodes[in].name, name.c_str());
    return in;
}

void write_file(int fd, int x)
{
    printf("Enter text to write into file and write end in a new line to end writing\n");
    string s, store, comp_str = "";
    int error = 0;
    // string s;
    while (getline(cin, s) && s != "end")
    {
        comp_str = comp_str + s + "\n";
    }
    //cout<<comp_str;
    //cout<<comp_str.length();
    int file_size = comp_str.length();
    inodes[fd].size = file_size;
    int prev = -1, start = 0, end = 0;
    bool first = true;

    while (file_size)
    {
        int ib;
        ib = find_empty_block();
        if (false || x == 0)
        {
            blocks[inodes[fd].last_block].next_block = ib;
            if (x != 0)
            {
                printf("error while writing the file");
            }
            x = 2;
        }
        sb.bit_block[ib] = 1;
        if (false || (first == true && x == 1))
        {
            inodes[fd].first_block = ib;
            bool val = false;
            first = val;
        }
        if (prev != -1 && true)
        {
            blocks[prev].next_block = ib;
        }
        int cur = min(510, file_size);
        if (error)
        {
            cout << "error occured";
        }
        store = comp_str.substr(start, cur);
        strcpy(blocks[ib].data, store.c_str());
        //blocks[ib].data=(*store);
        prev = ib;
        file_size = file_size - cur;
    }
    inodes[fd].last_block = prev;
    blocks[prev].next_block = -2;
    printf("Contents written into file\n");
}

void read_file(int fd)
{
    int testing = 0;
    if (inodes[fd].first_block == -1)
    {
        cout << "No file exists";
        return;
    }
    int flag = 1, first = inodes[fd].first_block;
    int last = inodes[fd].last_block;
    while (false || first != last)
    {
        flag = 0;
        cout << blocks[first].data;
        testing = 22;
        first = blocks[first].next_block;
    }
    cout << blocks[last].data;
    printf("File content read successfully\n");
}
void append_file(int fd)
{
    if (inodes[fd].first_block == -1)
    {
        printf("No previous content exists");
    }
    else
    {
        ;
        // do nothing
    }
    write_file(fd, 0);
}
void sync_disk(string str)
{
    size_t temp;
    FILE *file = fopen(str.c_str(), "w+");
    temp = fwrite(&sb, sizeof(super_block), 1, file);
    temp = fwrite(inodes, sizeof(inode) * sb.num_of_inode, 1, file);
    temp = fwrite(blocks, sizeof(block) * sb.num_of_blocks, 1, file);
    fclose(file);
}
void read_disk(string str)
{
    size_t temp;
    int closeVal;
    FILE *file = fopen(str.c_str(), "r");
    fread(&sb, sizeof(super_block), 1, file);
    blocks = (block *)malloc(sizeof(struct block) * sb.num_of_blocks);

    inodes = (inode *)malloc(sizeof(struct inode) * sb.num_of_inode);
    // inodes=new inode[sb.num_of_inode];
    // blocks=new block[sb.num_of_blocks];
    temp = fread(inodes, sizeof(inode), sb.num_of_inode, file);
    temp = fread(blocks, sizeof(block), sb.num_of_blocks, file);
    closeVal = fclose(file);
}

int main()
{
    while (true)
    {
        int choice;
        bool switch_flag = false;
        printf("\n-------------------------------------------\n");
        printf("1. Create Disk\n2. Mount Disk\n3. Exit\n");
        printf("Enter the choice\n");
        cin >> choice;
        if (false || choice == 1)
        {
            string disk;
            int x;
            cout << "Enter the disk name\n";
            cin >> disk;
            x = create_disk(disk);
            if (x == -1)
            {
                cout << "Disk Creation failed\n";
            }
            else
            {
                cout << "Disk is successfully created\n";
            }
        }
        else if (choice == 2)
        {
            string file_name;
            cout << "Enter disk name\n";
            cin >> file_name;
            read_disk(file_name);
            cout << "Disk mounted\n";
            switch_flag = true;
            while (switch_flag)
            {
                printf("\n-------------------------------------------\n");
                printf("1. Create File\n2. Open File\n3. Read File\n4. Write File\n5. Append File\n6. Close File\n7. Delete File\n8. List of files\n9. List of opened files\n10. Unmount\n");
                printf("Enter the choice\n");
                int cho;
                cin >> cho;
                switch (cho)
                {
                case 1:
                {
                    cout << "Enter File Name\n";
                    string filename;
                    cin >> filename;
                    int x;
                    x = create_file(filename);
                    
                    cout << x << "\n";
                    file_to_descriptor[filename] = x;
                    break;
                }
                
                case 2:
                {
                    cout << "Enter file name\n";
                    string filename;
                    int fd;
                    cin >> filename;
                    if (file_to_descriptor.find(filename) == file_to_descriptor.end())
                    {
                        cout << "File doesn't exists\n";
                        break;
                    }
                    fd = file_to_descriptor[filename];

                    cout << "Enter the mode to open file\n";
                    printf("0. Read\n1. Write\n2. Append\n");
                    int mode;
                    cin >> mode;
                    inodes[fd].mode = mode;
                    cout << "Opened file in given mode\n";
                    
                    break;
                }
               
                case 3:
                {
                  
                    cout << "Enter file name\n";
                    string filename;
                    int fd;
                    cin >> filename;
                    if (file_to_descriptor.find(filename) == file_to_descriptor.end())
                    {
                        cout << "File doesn't exists\n";
                        break;
                    }
                    fd = file_to_descriptor[filename];
                
                    if (inodes[fd].mode != 0)
                    {
                        cout << "File not opened in required mode\n";
                    }
                    else
                    {
                        read_file(fd);
                    }
                    break;
                }
                
                case 4:
                {
                   

                    cout << "Enter file name\n";
                    string filename;
                    int fd;
                    cin >> filename;
                    if (file_to_descriptor.find(filename) == file_to_descriptor.end())
                    {
                        cout << "File doesn't exists\n";
                        break;
                    }
                    fd = file_to_descriptor[filename];
                  ;
                    if (inodes[fd].mode != 1)
                    {
                        cout << "File not opened in required mode\n";
                    }
                    else
                    {
                        write_file(fd, 1);
                    }
                    break;
                }
                
                case 5:
                {
                    cout << "Enter file name\n";
                    string filename;
                    int fd;
                    cin >> filename;
                    if (file_to_descriptor.find(filename) == file_to_descriptor.end())
                    {
                        cout << "File doesn't exists\n";
                        break;
                    }
                    fd = file_to_descriptor[filename];
                    if (inodes[fd].mode != 2)
                    {
                        cout << "File not opened in required mode\n";
                    }
                    else
                    {
                        append_file(fd);
                    }
                    break;
                }
                case 6:
                {
                    cout << "Enter file name\n";
                    string filename;
                    int fd;
                    cin >> filename;
                    if (file_to_descriptor.find(filename) == file_to_descriptor.end())
                    {
                        cout << "File doesn't exists\n";
                        break;
                    }

                    fd = file_to_descriptor[filename];
                    if (inodes[fd].mode != -1)
                    {

                        inodes[fd].mode = -1;
                        cout << "File closed\n";
                        break;
                    }
                    else
                    {
                        cout << "File is not opened\n";
                        break;
                    }
                }
                case 8:
                    {
                        cout << "list of files: \n";
                        for (auto &x : file_to_descriptor)
                            cout << x.first << endl;
                        break;
                    }
                case 9:
                {
                    cout << "list of opened files:\n";
                    for (int i = 0; i < sb.num_of_inode; i++)
                    {
                        if (inodes[i].mode != -1)
                        {
                            cout << inodes[i].name << endl;
                        }
                    }
                    break;
                }
                case 10:
                {
                    cout << "unmounted\n";
                    switch_flag = false;
                    break;
                }
                default:
                    cout << "Invalid Choice\n";
                    break;
                }
            }
            sync_disk(file_name);
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Enter correct choice\n");
        }
    }
}