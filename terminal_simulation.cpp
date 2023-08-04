#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Node 
{
    public:
    string dirName;
    Node* parent;
    vector<Node*> children;
    vector<string> files;
    vector<string> folderNames;
    string pwd_ans;
    string read()
    {
        return dirName;
    }
    Node(string name, string prev_pwd, Node* parDir)
    {
        dirName = name;
        parent = parDir;
        if(prev_pwd != "")
        pwd_ans = prev_pwd + "/" + name;
        else
        pwd_ans = name;
    }
    Node* cd(string name, Node* curDir)
    {
        for(int i=0; i<(int)children.size(); ++i)
        {
            if(children[i]->dirName==name)
            {
                return children[i];
            }
        }
        cout<<"Folder does not exist"<<endl;
        return curDir;
    }
    void mkdir(string name, Node* parDir)
    {
        for(int i=0; i<(int)children.size(); ++i)
        {
            if(children[i]->dirName==name)
            {
                cout<<"Folder Exists"<<endl;
                return;
            }
        }
        for(int i=0; i<(int)files.size(); ++i)
        {
            if(files[i]==name)
            {
                cout<<"File Exists"<<endl;
                return;
            }
        }
        Node* temp = new Node(name, pwd_ans, parDir);
        children.push_back(temp);
    }
    void touch(string name)
    {
        for(int i=0; i<(int)children.size(); ++i)
        {
            if(children[i]->dirName==name)
            {
                cout<<"Folder Exists"<<endl;
                return;
            }
        }
        for(int i=0; i<(int)files.size(); ++i)
        {
            if(files[i]==name)
            {
                cout<<"File Exists"<<endl;
                return;
            }
        }
        files.push_back(name);
    }
    string pwd()
    {
        return pwd_ans;
    }
    void rm(string name)
    {
        for(int i=0; i<(int)children.size(); ++i)
        {
            if(children[i]->dirName==name)
            {
                children.erase(children.begin()+i);
                return;
            }
        }
        for(int i=0; i<(int)files.size(); ++i)
        {
            if(files[i]==name)
            {
                files.erase(files.begin()+i);
                return;
            }
        }
        cout<<"Does not exist"<<endl;
    }
    void ls()
    {
        folderNames.clear();
        for(int i=0; i<(int)children.size(); ++i)
        {
            folderNames.push_back(children[i]->dirName);
        }
        sort(folderNames.begin(),folderNames.end());
        for(int i=0; i<(int)folderNames.size(); ++i)
        {
            cout<<folderNames[i]<<" ";
        }
        sort(files.begin(),files.end());
        for(int i=0; i<(int)files.size(); ++i)
        {
            cout<<files[i]<<" ";
        }
        cout<<endl;
    }
};

int main() {
    string terminalName, username;
    cin>>terminalName>>username;
    string currentDirectory = "";
    string command;
    cin>>command;
    vector<pair<string,string>> history;
    Node* curDir = new Node(currentDirectory, "", NULL);
    curDir->mkdir("home", curDir);
    curDir = curDir->cd("home", curDir);
    curDir->mkdir(username, curDir);
    curDir = curDir->cd(username, curDir);
    Node* tempDir = curDir;
    while(command != "quit")
    {
        if(terminalName=="zsh")
        {
            cout<<username<<" ";
        }
        if(terminalName=="bash" || terminalName=="zsh")
        {
            cout<<"/"<<curDir->pwd()<<" ";
        }
        cout<<"$ "<<command<<" ";
        if(command=="mkdir")
        {
            string folderName;
            cin>>folderName;
            cout<<folderName<<endl;
            history.push_back(make_pair("mkdir", folderName));
            curDir->mkdir(folderName, curDir);
        }
        else if(command=="ls")
        {
            history.push_back({"ls", ""});
            cout<<endl;
            curDir->ls();
        }
        else if(command=="cd")
        {
            string toWhich;
            cin>>toWhich;
            cout<<toWhich<<endl;
            history.push_back(make_pair("cd", toWhich));
            if(toWhich!="~" && toWhich !="..")
            curDir = curDir->cd(toWhich, curDir);
            else if(toWhich=="~" && terminalName!="sh")
            curDir = tempDir;
            else if(toWhich=="~" && terminalName=="sh")
            curDir = curDir->cd(toWhich, curDir);  
            else
            {
                if(curDir->parent!=NULL)
                {
                    curDir = curDir->parent;
                }
            }
        }
        else if(command=="touch")
        {
            string fileName;
            cin>>fileName;
            cout<<fileName<<endl;
            history.push_back(make_pair("touch", fileName));
            curDir->touch(fileName);
        }
        else if(command=="pwd")
        {
            cout<<endl;
            history.push_back(make_pair("pwd", ""));
            cout<<"/"<<curDir->pwd()<<endl;
        }
        else if(command=="rm")
        {
            string fileOrFolderName;
            cin>>fileOrFolderName;
            cout<<fileOrFolderName<<endl;
            history.push_back(make_pair("rm", fileOrFolderName));
            curDir->rm(fileOrFolderName);
        }
        else if(command=="history" && terminalName == "zsh")
        {
            cout<<endl;
            for(int i=0; i<history.size(); ++i)
            {
                cout<<i<<" "<<history[i].first<<" "<<history[i].second<<endl;
            }
        }
        else
        {
            cout<<endl;
            history.push_back(make_pair(command, ""));
            cout<<"Command does not exist"<<endl;
        }
        cin>>command;
    }
    if(terminalName=="zsh")
    {
        cout<<username<<" ";
    }
    if(terminalName=="bash" || terminalName=="zsh")
    {
        cout<<"/"<<curDir->pwd()<<" ";
    }
    cout<<"$ "<<command<<" ";
    return 0;
}
