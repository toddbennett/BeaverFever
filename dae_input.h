#ifndef DAE_INPUT_H
#define DAE_INPUT_H

class DAENode
{
private:
	char *name;
	char **attributes;
	DAENode *children;
public:
	DAENode(char *text);
};

class DAETree
{
private:
	DAENode *root;
public:
	DAETree(char *filename);
};

#endif
