/*
Trên ngôn ngữ C/C++, viết chương trình thực hiện yêu cầu sau:

1 : Định nghĩa một cấu trúc Học viên bao gồm các trường thông tin như sau:
	Mã học viên (kiểu số nguyên),
	tên học viên (kiểu chuỗi ký tự),
	lớp (kiểu chuỗi ký tự),
	chuyên ngành (Khoa học máy tính, Thương mại điện tử, Quản trị an ninh mạng,
	điểm tổng kết (kiểu số thực).
2 : Cài đặt một cấu trúc danh sách liên kết đôi cho kiểu dữ liệu Học viên, với các thao tác:
	1) Khởi tạo danh sách;
	2) Tạo mới một nút chứa dữ liệu;
	3) Chèn nút vào đầu danh sách;
	4) Duyệt danh sách.
3 : Chương trình chính: Sử dụng cấu trúc danh sách liên kết đơn và các thao tác đã tạo để:
	– Nhập và 1 danh sách gồm n Học viên (n bất kỳ).
	– Hiển thị danh sách đã nhập ra màn hình.
	– Liệt kê ra màn hình danh sách tất cả những Học viên thuộc chuyên ngành “Thương mại điện tử” và có điểm tổng kết ≥ 8.0
	- Nhập vào mã học viên và xóa học viên đó khỏi danh sách
	- Hiển thị lại danh sách sau khi xóa học viên
*/
#include <iostream>
#include <string>

using namespace std;
struct HocVien
{
	int Ma;
	string Ten;
	string Lop;
	string Nganh;
	float Diem;
};
struct node
{
	HocVien Data;
	node* Next;
	node* Prev;
};
node* MakeNode(HocVien HV)
{
	node* NewNode = new node();
	NewNode->Data = HV;
	NewNode->Next = NULL;
	NewNode->Prev = NULL;
	return NewNode;
}
void Push_Front(node*& head, HocVien& HV)
{
	node* NewNode = MakeNode(HV);
	NewNode->Next = head;
	if (head != NULL)
	{
		head->Prev = NewNode;
	}
	head = NewNode;
}
void Push_Back(node*& head, HocVien& HV)
{
	node* newnode = MakeNode(HV);
	node* temp = head;
	if (head == NULL)
	{
		head = newnode;
		return;
	}
	while (temp->Next != NULL)
	{
		temp = temp->Next;
	}
	temp->Next = newnode;
	newnode->Prev = temp;
}
void Nhap_Nganh(HocVien*& HV)
{

	cout << "1.Khoa Hoc May Tinh" << endl;
	cout << "2.Thuong Mai Dien Tu" << endl;
	cout << "3.Quan Tri An Ninh Mang" << endl;
	int x;
	do
	{

		cout << "Nganh hoc cua ban la: ";
		cin >> x;
	} while (x != 1 && x != 2 && x != 3);
	if (x == 1)
	{
		HV->Nganh = "Khoa Hoc May Tinh";
	}
	else if (x == 2)
	{
		HV->Nganh = "Thuong Mai Dien Tu";
	}
	else if (x == 3)
	{
		HV->Nganh = "Quan Tri An Ninh Mang";
	}
}
HocVien* Nhap_1_Hoc_Vien(HocVien*& HV)
{
	cout << "Nhap ma hoc vien: ";
	cin >> HV->Ma;
	cout << "Nhap ten hoc vien: ";
	cin.ignore();
	getline(cin, HV->Ten);
	cout << "Nhap lop: ";
	getline(cin, HV->Lop);
	Nhap_Nganh(HV);
	cout << "Nhap diem: ";
	cin >> HV->Diem;
	return HV;
}
void Nhap_n_hoc_vien_vao_dau(node*& head)
{
	int n;
	cout << "nhap so luong hoc vien: ";
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		HocVien* HV = new HocVien();
		HV = Nhap_1_Hoc_Vien(HV);
		Push_Front(head, *HV);
	}
}
void Nhap_n_hoc_vien_vao_cuoi(node*& head)
{
	int n;
	cout << "nhap so luong hoc vien: ";
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		HocVien* HV = new HocVien();
		HV = Nhap_1_Hoc_Vien(HV);
		Push_Back(head, *HV);
	}
}
void liet_ke_hsg_tmdt(node* head)
{
	cout << "\nnhung sinh vien thuoc nganh thuong mai dien tu va co so diem tren 8.0 la: " << endl;
	for (node* temp = head; temp != NULL; temp = temp->Next)
	{
		if (temp->Data.Nganh == "Thuong Mai Dien Tu" && temp->Data.Diem >= 8.0)
		{
			cout << temp->Data.Ma << ", " << temp->Data.Ten << ", " << temp->Data.Lop << ", " << temp->Data.Nganh << ", " << temp->Data.Diem << endl;
		}
	}
}
void Pop_Front(node*& head)
{
	if (head == NULL)return;
	node* temp = head;
	head = temp->Next;
	head->Prev = NULL;
	delete(temp);
}
int sz(node* head)
{
	int cnt=0;
	while (head != NULL)
	{
		cnt++;
		head = head->Next;
	}
	return cnt;
}
void Earse(node*& head,int k)
{
	node* temp = head;
	while (temp != NULL)
	{
		if (temp->Data.Ma == k)
		{
			temp->Prev->Next = temp->Next;
			temp->Next->Prev = temp->Prev;
			
		}
		temp = temp->Next;
	}
	delete(temp);
}
void duyet(node* head)
{
	while (head != NULL)
	{
		cout << head->Data.Ma << ", " << head->Data.Ten << ", " << head->Data.Lop << ", " << head->Data.Nganh << ", " << head->Data.Diem << endl;
		head = head->Next;
	}
}
void menu()
{
	node* head = NULL;
	while (true)
	{
		cout << endl;
		cout << "=============================================" << endl;
		cout << "1. Them n hoc vien vao dau danh sach" << endl;
		cout << "2. Them n hoc vien vao cuoi danh sach" << endl;
		cout << "3. Liet ke nhung sinh vien gioi nganh tmdt" << endl;
		cout << "4. Xoa mot hoc vien ra khoi danh sach va duyet lai" << endl;
		cout << "5. Duyet" << endl;
		cout << "=============================================" << endl;
		int luachon;
		cout << "nhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			Nhap_n_hoc_vien_vao_dau(head);
		}
		else if (luachon == 2)
		{
			Nhap_n_hoc_vien_vao_cuoi(head);
		}
		else if (luachon == 3)
		{
			liet_ke_hsg_tmdt(head);
		}
		else if (luachon == 4)
		{
			int k;
			cout << "nhap ma hoc vien muon xoa: ";
			cin >> k;
			Earse(head, k);
			cout << "\ndanh sach sau khi xoa hoc vien co ma " << k << " la: " << endl;
			duyet(head);
			
		}
		else if (luachon == 5)
		{
			duyet(head);
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