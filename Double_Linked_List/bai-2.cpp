/*
* Viết chương trình trong ngôn ngữ C thực hiện các yêu cầu sau:
	Khai báo cấu trúc dữ liệu để tổ chức danh sách liên kết đơn
	quản lý các tỉnh/thành phố của Việt Nam.

	Thông tin của mỗi tỉnh/thành phố bao gồm: Mã tỉnh, tên tỉnh, diện tích, dân số.
	Cài đặt các thao tác cơ bản (thêm ở vị trí bất kỳ; sửa, xóa theo mã (code),
	duyệt danh sách).

	Tính tổng diện tích của tất cả các tỉnh thành.
	Tìm vị trí của node của tỉnh có diện tích lớn nhất.
	Tìm tỉnh/thành phố có dân số lớn nhất.
	Sắp xếp danh sách theo mã tỉnh/thành phố.
	Sắp xếp danh sách tăng dần theo diện tích.
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Province
{
	int ID;
	string Name;
	double Area;
	long long Population;
};
struct Node
{
	Province Data;
	Node* Next;
	Node* Prev;
};
Node* MakeNode(Province Pro)
{
	Node* NewNode = new Node();
	NewNode->Data = Pro;
	NewNode->Next = NULL;
	NewNode->Prev = NULL;
	return NewNode;
};
Province* Read_One_Province(ifstream& File_Province_In, Province*& Pro)
{
	File_Province_In >> Pro->ID;
	File_Province_In.ignore();
	getline(File_Province_In, Pro->Name, ',');
	File_Province_In >> Pro->Area;
	File_Province_In.seekg(1, 1);
	File_Province_In >> Pro->Population;
	return Pro;
}
void Push_Front(Node*& head, Province*& Pro)
{
	Node* NewNode = MakeNode(*Pro);
	NewNode->Next = head;
	if (head != NULL)
	{
		head->Prev = NewNode;
	}
	head = NewNode;
}
void Push_Back(Node*& head, Province*& Pro)
{
	Node* NewNode = MakeNode(*Pro);
	Node* Temp = head;
	if (head == NULL)
	{
		head = NewNode;
		return;
	}
	while (Temp->Next != NULL)
	{
		Temp = Temp->Next;
	}
	Temp->Next = NewNode;
	NewNode->Prev = Temp;
}
Province* Nhap_1_Tinh(Node*& head, Province*& Pro)
{
	cout << "Nhap ma tinh: ";
	cin >> Pro->ID;
	cout << "Nhap ten tinh: ";
	cin.ignore();
	getline(cin, Pro->Name);
	cout << "Nhap dien tich tinh: ";
	cin >> Pro->Area;
	cout << "Nhap dan so: ";
	cin >> Pro->Population;
	return Pro;
}
void Read_File_Province(Node*& head)
{
	ifstream File_Province_In;
	File_Province_In.open("Province.txt", ios_base::in);
	if (!File_Province_In.is_open())
	{
		cerr << "Fail to open file province" << endl;
		return;
	}
	while (!File_Province_In.eof())
	{
		Province* Pro = new Province();
		Pro = Read_One_Province(File_Province_In, Pro);
		Push_Back(head, Pro);
	}
	File_Province_In.close();
}
int sz(Node* head)
{
	int cnt = 0;
	while (head != NULL)
	{
		++cnt;
		head = head->Next;
	}
	return cnt;
}
void them_mot_tinh_bat_ky(Node*& head, int k,Province *&Pro)
{
	int n = sz(head);
	
	if (k <1 || k > n+1)return;
	if (k == 1)
	{
		Push_Front(head, Pro);
		return;
	}
	else
	{
		Node* temp = head;
		
		for (int i = 1; i <= k - 1; i++)
		{
			temp = temp->Next;
		}
		Node* NewNode = MakeNode(*Pro);
		NewNode->Next = temp;
		temp->Prev->Next = NewNode;
		NewNode->Prev = temp->Prev;
		temp->Prev = NewNode;
	}
}
void Edit_ID(Node*& head,int id)
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->Data.ID == id)
		{
			int newid;
			cout << "Nhap ma tinh moi: ";
			cin >> newid;
			temp->Data.ID = newid;
			break;
		}
		temp = temp->Next;
	}
}
void Edit_Name(Node*& head, string x)
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->Data.Name == x)
		{
			string newname;
			cout << "Nhap ten tinh moi: ";
			getline(cin, newname);
			temp->Data.Name = newname;
			break;
		}
		temp = temp->Next;
	}
}
void Edit_Area(Node*& head, string x)
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->Data.Name == x)
		{
			double newarea;
			cout << "Nhap dien tich moi: ";
			cin >> newarea;
			temp->Data.Area = newarea;
			break;
		}
		temp = temp->Next;
	}
}
void Edit_Population(Node*& head, string x)
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->Data.Name == x)
		{
			long long newpop;
			cout << "Nhap so dan moi: ";
			cin >> newpop;
			temp->Data.Population = newpop;
			break;
		}
		temp = temp->Next;
	}
}
void Edit(Node*& head)
{
	system("cls");
	while (true)
	{
		cout << "\n\n\t\t\t=======================================" << endl;
		cout << "\t\t\t= 1. Sua ma tinh" << endl;
		cout << "\t\t\t= 2. Sua ten tinh" << endl;
		cout << "\t\t\t= 3. Sua dien tich" << endl;
		cout << "\t\t\t= 4. Sua dan so" << endl;
		cout << "\t\t\t= 0. Thoat" << endl;
		cout << "\t\t\t=======================================" << endl;
		int luachon;
		cout << "Nhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			int id;
			cout << "Nhap ma tinh ban muon thay the: ";
			cin >> id;
			Edit_ID(head, id);
			cout << "Sua thanh cong " << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 2)
		{
			string tentinh;
			cout << "nhap ten tinh can chinh sua: ";
			cin.ignore();
			getline(cin, tentinh);
			Edit_Name(head, tentinh);
			cout << "Sua thanh cong " << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 3)
		{
			string tentinh;
			cout << "nhap ten tinh can chinh sua: ";
			cin.ignore();
			getline(cin, tentinh);
			Edit_Area(head, tentinh);
			cout << "Sua thanh cong " << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 4)
		{
			string tentinh;
			cout << "nhap ten tinh can chinh sua: ";
			cin.ignore();
			getline(cin, tentinh);
			Edit_Population(head, tentinh);
			cout << "Sua thanh cong " << endl;
			system("pause");
			system("cls");
		}
		else
		{
			break;
		}
	}
}

void Pop_Front(Node*& head)
{
	if (head == NULL)return;
	Node* temp = head;
	head = temp->Next;
	head->Prev = NULL;
	delete(temp);
}
void Earse(Node*& head, int k)
{
	int n = sz(head);
	if (k < 1 || k> n)return;
	if (k == 1)
	{
		Pop_Front(head);
		return;
	}
	else
	{
		Node* temp = head;
		for (int i = 1; i <= k - 1; i++)
		{
			temp = temp->Next;
		}
		temp->Next->Prev = temp->Prev;
		temp->Prev->Next = temp->Next;

	}
}
void duyet(Node* head)
{
	while (head != NULL)
	{
		cout << head->Data.ID << ", " << head->Data.Name << ", " << head->Data.Area << ", " << head->Data.Population << endl;
		head = head->Next;
	}
}
Node* Last_Node(Node* head)
{
	Node* temp = head;
	while (temp->Next != NULL)
	{
		temp = temp->Next;
	}
	return temp;
}
void hoanvi(Province*& a, Province*& b)
{
	Province* temp = a;
	a = b;
	b = temp;
}
Node* Partition(Node* First, Node* Last)
{
	Node* Pivot = First;
	Node* Front = First;
	Province temp;
	while (Front != NULL && Front != Last)
	{
		if (Front->Data.ID < Last->Data.ID)
		{
			Pivot = First;
			temp = First->Data;
			First->Data = Front->Data;
			Front->Data = temp;
			First = First->Next;
		}
		Front = Front->Next;
	}
	temp = First->Data;
	First->Data = Last->Data;
	Last->Data = temp;

	return Pivot;
}
void Quick_Sort(Node* First, Node* Last)
{
	if (First == Last)return;
	Node* Pivot = Partition(First, Last);
	if (Pivot != NULL && Pivot->Next != NULL)
	{
		Quick_Sort(Pivot->Next, Last);
	}
	if (Pivot != NULL && First != Pivot)
	{
		Quick_Sort(First, Pivot);
	}
}
void menu()
{
	Node* head = NULL;
	while (true)
	{
		cout << "\n\n\t\t\t=======================================" << endl;
		cout << "\t\t\t= 1. Them 1 tinh vao dau danh sach" << endl;
		cout << "\t\t\t= 2. Them 1 tinh vao cuoi danh sach" << endl;
		cout << "\t\t\t= 3. Them 1 tinh vao vi tri bat ky" << endl;
		cout << "\t\t\t= 4. Doc danh sach tinh thanh tu file" << endl;
		cout << "\t\t\t= 5. Sua thong tin tinh thanh" << endl;
		cout << "\t\t\t= 6. Xoa mot tinh bang ma tinh" << endl;
		cout << "\t\t\t= 7. Sap xep theo ma tinh" << endl;
		cout << "\t\t\t= 9. Duyet" << endl;
		cout << "\t\t\t= 0. Thoat" << endl;
		cout << "\t\t\t=======================================" << endl;
		int luachon;
		cout << "Nhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			Province* Pro = new Province();
			Pro = Nhap_1_Tinh(head, Pro);
			Push_Front(head, Pro);
			cout << "Them thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 2)
		{
			Province* Pro = new Province();
			Pro = Nhap_1_Tinh(head, Pro);
			Push_Back(head, Pro);
			cout << "Them thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 3)
		{
			int k;
			cout << "Nhap vi tri muon them: ";
			cin >> k;
			Province* Pro = new Province();
			Pro = Nhap_1_Tinh(head, Pro);
			them_mot_tinh_bat_ky(head, k,Pro);
			cout << "Them thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 4)
		{
			Read_File_Province(head);
			cout << "Doc thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 5)
		{
			Edit(head);
		}
		else if (luachon == 6)
		{
			int ma;
			cout << "Nha ma tinh can xoa: ";
			cin >> ma;
			Earse(head, ma);
			cout << "Xoa thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 7)
		{
			Quick_Sort(head, Last_Node(head));
			cout << "Danh sach sau khi sap xep theo ma tinh la: " << endl;
			duyet(head);
		}
		else if (luachon == 9)
		{
			duyet(head);
			system("pause");
			system("cls");
		}
		else
		{
			break;
		}
	}
}
int main()
{
	menu();
	return 0;
}