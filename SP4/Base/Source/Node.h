// Structure For Basic Unit/Node In Map
class Node
{
public:
	Node();
	Node *parent;	// Link To Previous Node On Best Path
	int x, y;		// x,y Position Of Grid
	float f, g, h;	// Cost Elements : g = Cost From Start To Current Node
	//                 h = Cost From Current To Goal Node
	//				   f = Cost From Start To Goal (g+h) Node
};