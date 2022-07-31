#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _1302


#ifdef _1301
#define MAX_LEN 32

typedef enum { Term, Insert, Search, Print } Menu;

typedef struct __bnode {
	char name[MAX_LEN];
	struct __bnode* left;
	struct __bnode* right;
} BinNode;

BinNode* AllocNode() {
	return (BinNode*)calloc(1, sizeof(BinNode));
}

BinNode* InsertNode(BinNode* p, const BinNode* w) {
	int cond = 0;

	if (p == NULL) {
		p = AllocNode();
		strcpy_s(p->name, w->name);
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w->name, p->name)) == 0) {
		printf("【エラー】%sは既に登録されています。\n", w->name);
	}
	else if (cond < 0) {
		p->left = InsertNode(p->left, w);
	}
	else {
		p->right = InsertNode(p->right, w);
	}

	return p;
}

void SearchNode(BinNode* p, BinNode* w) {
	int cond = 0;

	if (p == NULL) {
		printf("%sは登録されていません。\n", w->name);
	}
	else if ((cond = strcmp(w->name, p->name)) == 0) {
		printf("%sは登録されています。\n", w->name);
	}
	else if (cond < 0) {
		SearchNode(p->left, w);
	}
	else {
		SearchNode(p->right, w);
	}
}

void PrintTree(const BinNode* p) {
	if (p != NULL) {
		PrintTree(p->left);
		printf("%s\n", p->name);
		PrintTree(p->right);
	}
}

void FreeTree(BinNode* p) {
	if (p != NULL) {
		FreeTree(p->left);
		FreeTree(p->right);
		free(p);
	}
}

BinNode Read(const char* message) {
	BinNode temp{};

	printf("%sする名前を入力してください : ", message);
	scanf_s("%s", temp.name, MAX_LEN);
	
	return temp;
}

Menu SelectMenu() {
	int ch = 0;

	do {
		printf("\n(1) 挿入  (2) 探索  (3) 表示  (0) 終了 : ");
		scanf_s("%d", &ch);
	} while (ch < Term || ch > Print);

	return (Menu)ch;
}

int main(void) {
	Menu menu{};
	BinNode* root{};

	root = NULL;
	do {
		BinNode x;
		switch (menu = SelectMenu()) {
		case Insert :
			x = Read("挿入");
			root = InsertNode(root, &x);
			break;
		case Search:
			x = Read("探索");
			SearchNode(root, &x);
			break;
		case Print:
			puts("--- 一覧表 ---");
			PrintTree(root);
			break;
		}
	} while (menu != Term);

	FreeTree(root);

	return 0;
}
#endif

#ifdef _1302
#define MAX_LEN 32
#define STK_SIZE 64

typedef enum { Term, Insert, Search, Next, Prev, Print } Menu;

typedef struct __bnode {
	char name[MAX_LEN];
	struct __bnode* left;
	struct __bnode* right;
} BinNode;

BinNode* AllocNode() {
	return (BinNode*)calloc(1, sizeof(BinNode));
}

BinNode* stk[STK_SIZE];
int ptr;

void Error() {
	puts("Error");
}

BinNode* InsertNode(BinNode* p, const BinNode* w) {
	int cond = 0;

	if (p == NULL) {
		p = AllocNode();
		strcpy_s(p->name, w->name);
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w->name, p->name)) == 0) {
		printf("【エラー】%sは既に登録されています。\n", w->name);
	}
	else if (cond < 0) {
		p->left = InsertNode(p->left, w);
	}
	else {
		p->right = InsertNode(p->right, w);
	}

	return p;
}

void SearchNode(BinNode* root, const BinNode* w) {
	if (root != NULL) {
		BinNode* p = root;
		ptr = 0;

		while (true) {
			if (p != NULL) {
				int cond = 0;

				stk[ptr++] = p;
				if ((cond = strcmp(w->name, p->name)) == 0) {
					printf("%sは既に登録されています。\n", w->name);
					ptr--;
					break;
				}
				p = (cond < 0) ? p->left : p->right;
			}
			else {
				printf("%sは登録されていません。\n", w->name);
				ptr = -1;
				break;
			}
		}
	}
}

BinNode* SearchMinMax(const BinNode* root, int sw) {
	if (root == NULL) return NULL;
	else {
		BinNode* p = (BinNode*)root;

		while (p != NULL) {
			stk[++ptr] = p;
			p = (sw == 0) ? p->left : p->right;
		}
		return stk[ptr];
	}
}

void SrchNext() {
	if (ptr == -1) Error();
	else {
		BinNode* p = nullptr;

		if (stk[ptr]->right != NULL) {
			p = SearchMinMax(stk[ptr]->right, 0);
		}
		else {
			char* name = stk[ptr]->name;
			while (true) {
				if (--ptr < 0) {
					p = NULL;
					break;
				}
				if (strcmp(stk[ptr]->name, name) > 0) {
					p = stk[ptr];
					break;
				}
			}
		}
		if (p == NULL) Error();
		else printf("データは [%s] です。\n", p->name);
	}
}

void SrchPrev() {
	if (ptr == -1) Error();
	else {
		BinNode* p = NULL;

		if (stk[ptr]->left != NULL) {
			p = SearchMinMax(stk[ptr]->left, 1);
		}
		else {
			char* name = stk[ptr]->name;
			while (true) {
				if (--ptr < 0) {
					p = NULL;
					break;
				}
				else {
					if (strcmp(stk[ptr]->name, name) < 0) {
						p = stk[ptr];
						break;
					}
				}
			}
		}
		if (p == NULL) Error();
		else printf("データは [%s] です。\n", p->name);
	}
}

void PrintTree(const BinNode* root) {
	if (root != NULL) {
		BinNode* p = (BinNode*)root;
		BinNode* stk[STK_SIZE]{};
		int ptr = 0;

		while (true) {
			if (p != nullptr) {
				stk[ptr++] = p;
				p = p->left;
			}
			else if (ptr > 0) {
				p = stk[--ptr];
				printf("%s\n", p->name);
				p = p->right;
			}
			else break;
		}
	}
}

void FreeTree(BinNode* p) {
	if (p != NULL) {
		FreeTree(p->left);
		FreeTree(p->right);
		free(p);
	}
}

BinNode Read(const char* message) {
	BinNode temp{};

	printf("%sする名前を入力してください : ", message);
	scanf_s("%s", temp.name, MAX_LEN);

	return temp;
}

Menu SelectMenu() {
	int ch = 0;

	do {
		printf("\n(1) 挿入  (2) 探索  (3) 次ノード  (4)前ノード  (5)表示  (0)終了 : ");
		scanf_s("%d", &ch);
	} while (ch < Term || ch > Print);

	return (Menu)ch;
}

int main(void) {
	Menu menu{};
	BinNode* root = nullptr;
	
	ptr = -1;
	do {
		BinNode x{};
		switch (menu = SelectMenu()) {
		case Insert:
			x = Read("挿入");
			root = InsertNode(root, &x);
			break;
		case Search:
			x = Read("探索");
			SearchNode(root, &x);
			break;
		case Next:
			SrchNext();
			break;
		case Prev:
			SrchPrev();
			break;
		case Print:
			puts("--- 一覧表 ---");
			PrintTree(root);
			break;
		}
	} while (menu != Term);

	FreeTree(root);

	return 0;
}
#endif