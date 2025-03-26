#include <iostream>
#include <queue>
#include <stack>
#include <map>
using namespace std;

class DLLNode
{
public:
    char vertex[20];
    DLLNode *next;
    DLLNode *down;
} *Head;

class Graph : public DLLNode
{
public:
    DLLNode *create_Graph(DLLNode *Head);
    void display_Graph(DLLNode *Head);
    void DFS(DLLNode *Head);
    void BFS(DLLNode *Head);
};

DLLNode *Graph ::create_Graph(DLLNode *Head)
{
    int i, vertices;
    DLLNode *Newnode, *current, *temp;

    cout << "\n\t How Many Vertices in Graph: ";
    cin >> vertices;

    for (i = 0; i < vertices; i++)
    {
        Newnode = new DLLNode;

        cout << "\n\t Enter Vertex Name: ";
        cin >> Newnode->vertex;
        Newnode->next = NULL;
        Newnode->down = NULL;

        if (Head == NULL)
        {
            Head = Newnode;
            current = Head;
        }
        else
        {
            current->down = Newnode;
            current = Newnode;
        }
    }

    current = Head;
    while (current != NULL)
    {
        cout << "\n\t How Many Adjacent Vertices for " << current->vertex << ":  ";
        cin >> vertices;
        temp = current;
        for (i = 0; i < vertices; i++)
        {
            Newnode = new DLLNode;
            cout << "\n\t Enter Vertex Name: ";
            cin >> Newnode->vertex;

            Newnode->next = NULL;
            Newnode->down = NULL;

            temp->next = Newnode;
            temp = Newnode;
        }
        current = current->down;
    }

    return Head;
}

void Graph ::display_Graph(DLLNode *Head)
{
    DLLNode *current, *temp;

    current = Head;
    while (current != NULL)
    {
        cout << "\n\t " << current->vertex;
        temp = current->next;
        while (temp)
        {
            cout << "----->" << temp->vertex;
            temp = temp->next;
        }
        current = current->down;
    }
}
void Graph ::DFS(DLLNode *Head)
{
    if (Head == NULL)
        return;

    stack<DLLNode *> s;
    map<string, bool> visited;

    s.push(Head);

    while (!s.empty())
    {
        DLLNode *current = s.top();
        s.pop();

        if (!visited[current->vertex])
        {
            cout << current->vertex << " ";
            visited[current->vertex] = true;
        }

        // Traverse next (adjacent vertices)
        DLLNode *temp = current->next;
        while (temp)
        {
            if (!visited[temp->vertex])
            {
                s.push(temp);
            }
            temp = temp->next;
        }

        // Traverse down (to next main vertex)
        if (current->down && !visited[current->down->vertex])
        {
            s.push(current->down);
        }
    }
}
void Graph ::BFS(DLLNode *Head)
{
    if (Head == NULL)
        return;

    queue<DLLNode *> q;
    map<string, bool> visited;

    q.push(Head);
    visited[Head->vertex] = true;

    while (!q.empty())
    {
        DLLNode *current = q.front();
        q.pop();
        cout << current->vertex << " ";

        // Traverse next (adjacent vertices)
        DLLNode *temp = current->next;
        while (temp)
        {
            if (!visited[temp->vertex])
            {
                q.push(temp);
                visited[temp->vertex] = true;
            }
            temp = temp->next;
        }

        // Traverse down (to next main vertex)
        if (current->down && !visited[current->down->vertex])
        {
            q.push(current->down);
            visited[current->down->vertex] = true;
        }
    }
}


int main()
{
    cout << "\n\n.........Graph by Adjacency List............";

    Graph G1;
    Head = NULL;

    cout << "\n\n A] Create Graph using Linked List............\n";
    Head = G1.create_Graph(Head);

    cout << "\n\n B] Show Graph using Linked List............\n";
    G1.display_Graph(Head);

    cout << "\n\n C] Depth-First Search Traversal (using Stack)............\n";
    G1.DFS(Head);

    cout << "\n\n D] Breadth-First Search Traversal (using Queue)............\n";
    G1.BFS(Head);

    return 0;
}
