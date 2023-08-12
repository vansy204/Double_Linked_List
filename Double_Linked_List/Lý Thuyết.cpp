#include <iostream>
using namespace std;
struct node
{
	int data;
	node* next;
	node* prev;
};
node* MakeNode(int x)
{
	node* newnode = new node();
	newnode->data = x;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}
void duyet(node* head)
{
	while (head != NULL)
	{
		cout << head->data << " ";
		head = head->next;
	}
}
int count(node* head)
{
	int cnt = 0;
	while (head != NULL)
	{
		++cnt;
		head = head->next;
	}
	return cnt;
}
void Push_Front(node*& head, int x)
{
	node* newnode = MakeNode(x);
	newnode->next = head; // cho phần next của node mới trỏ vào node đầu hiện tại
	if (head != NULL)
	{
		head->prev = newnode;
	}

	head = newnode;
}
void Push_Back(node*& head, int x)
{
	node* newnode = MakeNode(x);
	node* temp = head;
	if (head == NULL)
	{
		head = newnode;
		return;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
	newnode->prev = temp;
}
void Insert(node*& head, int x, int k)
{
	int n = count(head);
	if (k <1 || k>n + 1)return;
	if (k == 1)
	{
		Push_Front(head, x);
		return;
	}
	node* temp = head;
	for (int i = 1; i <= k - 1; i++)
	{
		temp = temp->next;
	}
	node* newnode = MakeNode(x);
	newnode->next = temp;
	temp->prev->next = newnode;
	newnode->prev = temp->prev;
	temp->prev = newnode;
}
int main()
{
	node* head = NULL;
	while (true)
	{
		cout << endl;
		cout << "==================================" << endl;
		cout << "1. Them vao dau danh sach" << endl;
		cout << "2. Them vao cuoi danh sach" << endl;
		cout << "3. Them vao vi tri bat ky" << endl;
		cout << "4. Duyet" << endl;
		cout << "==================================" << endl;
		int luachon;
		cout << "nhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			int x;
			cout << "nhap x= "; cin >> x;
			Push_Front(head, x);
		}
		else if (luachon == 2)
		{
			int x;
			cout << "nhap x= "; cin >> x;
			Push_Back(head, x);
		}
		else if (luachon == 3)	
		{	int x;
			cout << "nhap x= "; cin >> x;
			int k;
			cout << "nhap vi tri muon chen: "; cin >> k;
			Insert(head, x, k);
		}
		else if (luachon == 4)
		{
			duyet(head);
		}
		else
		{
			break;
		}

	}
	return 0;
}