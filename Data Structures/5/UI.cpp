#include "Graph.cpp"

int main()
{
	vector<node*>Mst;
	cout << "Welcome to Graphs 1.0" << endl;
	int c;
	cout << "Enter Name of File: ";
	char buf[256];
	cin >> buf;
	Graph *g = new Graph(buf);
	while(true)
	{
		cout << endl << endl;
		cout << "Press 1 to Exit" << endl;
		cout << "Press 2 to run Kruskal on Graph"<< endl;
		cout << "Press 3 to run Prim's on Graph"<< endl;
		cout << "Press 4 to run Dijsktra on Graph"<< endl;
		cout << "Press 5 to Display a traversal of Graph"<< endl;
		cout << "Press 6 to Display last calculated MST"<< endl;
		cin >> c;
		cout << endl;

		if(c == 1)
		{
			break;
		}
		if(c == 2)
		{
			Mst = g->Kruskal();
			g = new Graph(buf);
		}
		if (c == 3) {
            Mst = g->Prims();
			g = new Graph(buf);
		}
		if(c == 4)
		{
			string buff;
			string buff2;
			cout << "Enter Name of Origin: ";
			cin >> buff;
			cout << "Enter Name of Destination: ";
			cin >> buff2;
			float d;
			g->Dijkstra(buff, buff2, d);
		}
		if(c == 5)
		{
			for(int i=0; i< g->cities.size(); i++)
				g->cities[i]->visit = 0;
			g->display(g->cities[1]);
		}
		if(c == 6)
		{
			if(Mst.size() < 1)
			{
				cout << "Run Kruskal or Prims first" << endl;
				continue;
			}
			for(int i=0; i< Mst.size(); i++)
				Mst[i]->visit = 0;
			g->display(Mst[0]);

            //g->mydisplay();
		}
	}
}
