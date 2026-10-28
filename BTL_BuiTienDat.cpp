#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;
const double LUONG_CO_SO = 1350000;
struct CanBo {
    int ma;
    string hoTen;      
    string phongBan;
    string chucVu;
    double heSoLuong;
};
struct Node {
    CanBo data;
    Node* next;
};
Node* taoNode(const CanBo& cb) {
    Node* p = new Node;
    p->data = cb;
    p->next = NULL;
    return p;
}
string docChuoi(const string& nhan) {
    string s;
    cout << nhan;
    getline(cin, s);
    return s;
}
int docSoNguyen(const string& nhan) {
    int x;
    cout << nhan;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Gia tri khong hop le, nhap lai: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}
double docSoThuc(const string& nhan) {
    double x;
    cout << nhan;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Gia tri khong hop le, nhap lai: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}
bool tonTaiMa(Node* head, int ma) {
    for (Node* p = head; p != NULL; p = p->next)
        if (p->data.ma == ma) return true;
    return false;
}
CanBo nhapThongTin(int ma) {
    CanBo cb;
    cb.ma = ma;
    cb.hoTen = docChuoi("  Ho dem va ten : ");
    cb.phongBan = docChuoi("  Phong ban     : ");
    cb.chucVu = docChuoi("  Chuc vu       : ");
    cb.heSoLuong = docSoThuc("  He so luong   : ");
    return cb;
}
int nhapMaKhongTrung(Node* head) {
    int ma = docSoNguyen("  Ma can bo (<=0 de dung): ");
    while (ma > 0 && tonTaiMa(head, ma)) {
        cout << "  Ma da ton tai! ";
        ma = docSoNguyen("Nhap lai ma can bo (<=0 de dung): ");
    }
    return ma;
}
int demNode(Node* head) {
    int n = 0;
    for (Node* p = head; p != NULL; p = p->next) n++;
    return n;
}
void inTieuDe() {
    cout << left << setw(8) << "Ma"
         << setw(28) << "Ho dem va ten"
         << setw(18) << "Phong ban"
         << setw(18) << "Chuc vu"
         << setw(10) << "He so" << endl;
    cout << string(82, '-') << endl;
}
void inCanBo(const CanBo& cb) {
    cout << left << setw(8) << cb.ma
         << setw(28) << cb.hoTen
         << setw(18) << cb.phongBan
         << setw(18) << cb.chucVu
         << setw(10) << fixed << setprecision(2) << cb.heSoLuong << endl;
}
void inDanhSach(Node* head) {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    inTieuDe();
    for (Node* p = head; p != NULL; p = p->next) inCanBo(p->data);
}
void taoDanhSach(Node*& head) {
    Node* tail = head;
    while (tail != NULL && tail->next != NULL) tail = tail->next;

    cout << "--- NHAP DANH SACH CAN BO ---\n";
    int stt = demNode(head) + 1;
    while (true) {
        cout << "Can bo thu " << stt << ":\n";
        int ma = nhapMaKhongTrung(head);
        if (ma <= 0) break;
        CanBo cb = nhapThongTin(ma);
        Node* p = taoNode(cb);
        if (head == NULL) head = tail = p;
        else { tail->next = p; tail = p; }
        stt++;
    }
    cout << "Da ket thuc nhap. Tong so can bo: " << demNode(head) << endl;
}
void themCanBo(Node*& head) {
    cout << "--- THEM CAN BO ---\n";
    int ma = docSoNguyen("  Ma can bo: ");
    if (ma <= 0) {
        cout << "Ma phai > 0!\n";
        return;
    }
    if (tonTaiMa(head, ma)) {
        cout << "Ma can bo da ton tai!\n";
        return;
    }
    CanBo cb = nhapThongTin(ma);
    int n = demNode(head);
    int pos = docSoNguyen("  Vi tri muon chen (1.." + to_string(n + 1) + "): ");
    Node* moi = taoNode(cb);
    if (pos <= 1 || head == NULL) {
        moi->next = head;
        head = moi;
    } else {
        if (pos > n + 1) pos = n + 1;
        Node* p = head;
        for (int i = 1; i < pos - 1; i++) p = p->next; 
        moi->next = p->next;
        p->next = moi;
    }
    cout << "Da them can bo thanh cong!\n";
}
double tinhLuong(const CanBo& cb) {
    return cb.heSoLuong * LUONG_CO_SO;
}

void inBangLuong(Node* head) {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    cout << left << setw(8) << "Ma"
         << setw(28) << "Ho dem, ten"
         << setw(10) << "He so"
         << setw(18) << "Luong (VND)" << endl;
    cout << string(64, '-') << endl;
    for (Node* p = head; p != NULL; p = p->next) {
        cout << left << setw(8) << p->data.ma
             << setw(28) << p->data.hoTen
             << setw(10) << fixed << setprecision(2) << p->data.heSoLuong
             << setw(18) << fixed << setprecision(0) << tinhLuong(p->data) << endl;
    }
}
void inHeSoLonHon(Node* head, double nguong = 4.4) {
    bool coKetQua = false;
    for (Node* p = head; p != NULL; p = p->next) {
        if (p->data.heSoLuong >= nguong) {
            if (!coKetQua) { inTieuDe(); coKetQua = true; }
            inCanBo(p->data);
        }
    }
    if (!coKetQua) cout << "Khong co can bo nao co he so luong >= " << nguong << endl;
}
void timTheoChucVu(Node* head) {
    string cv = docChuoi("Nhap chuc vu can tim: ");
    bool coKetQua = false;
    for (Node* p = head; p != NULL; p = p->next) {
        if (p->data.chucVu == cv) {
            if (!coKetQua) { inTieuDe(); coKetQua = true; }
            inCanBo(p->data);
        }
    }
    if (!coKetQua) cout << "Khong tim thay can bo co chuc vu \"" << cv << "\"\n";
}
void timTheoHeSoVaPhongBan(Node* head) {
    double hs = docSoThuc("Nhap he so luong can tim: ");
    string pb = docChuoi("Nhap phong ban can tim: ");
    bool coKetQua = false;
    for (Node* p = head; p != NULL; p = p->next) {
        double chenh = p->data.heSoLuong - hs;
        if (chenh < 0) chenh = -chenh;
        if (chenh < 1e-9 && p->data.phongBan == pb) {
            if (!coKetQua) { inTieuDe(); coKetQua = true; }
            inCanBo(p->data);
        }
    }
    if (!coKetQua) cout << "Khong tim thay can bo thoa man ca 2 dieu kien!\n";
}
string layTen(const string& hoTen) {
    size_t end = hoTen.find_last_not_of(' ');
    if (end == string::npos) return "";
    size_t pos = hoTen.find_last_of(' ', end);
    if (pos == string::npos) return hoTen.substr(0, end + 1);
    return hoTen.substr(pos + 1, end - pos);
}
bool lonHon(const CanBo& a, const CanBo& b) {
    string ta = layTen(a.hoTen), tb = layTen(b.hoTen);
    if (ta != tb) return ta > tb;
    return a.hoTen > b.hoTen; // cung ten thi xet ca ho ten
}
void sapXepTheoTen(Node* head) {
    if (head == NULL || head->next == NULL) return;
    bool doiCho;
    Node* cuoi = NULL;
    do {
        doiCho = false;
        Node* p = head;
        while (p->next != cuoi) {
            if (lonHon(p->data, p->next->data)) {
                CanBo tmp = p->data;
                p->data = p->next->data;
                p->next->data = tmp;
                doiCho = true;
            }
            p = p->next;
        }
        cuoi = p;
    } while (doiCho);
    cout << "Da sap xep danh sach theo ten (A -> Z).\n";
}
void huyDanhSach(Node*& head) {
    while (head != NULL) {
        Node* p = head;
        head = head->next;
        delete p;
    }
}
void hienMenu() {
    cout << "\n========== QUAN LY CAN BO ==========\n";
    cout << "1. Tao danh sach can bo\n";
    cout << "2. Them 1 can bo vao vi tri bat ky\n";
    cout << "3. Tinh luong cho can bo\n";
    cout << "4. In can bo co he so luong >= 4.4\n";
    cout << "5. Tim va in can bo theo chuc vu\n";
    cout << "6. Tim va in can bo theo he so luong va phong ban\n";
    cout << "7. Sap xep danh sach theo ten\n";
    cout << "8. In toan bo danh sach\n";
    cout << "0. Thoat\n";
    cout << "====================================\n";
}
int main() {
    Node* head = NULL;
    int chon;
    do {
        hienMenu();
        chon = docSoNguyen("Chon chuc nang: ");
        switch (chon) {
            case 1: taoDanhSach(head); break;
            case 2: themCanBo(head); break;
            case 3: inBangLuong(head); break;
            case 4: inHeSoLonHon(head); break;
            case 5: timTheoChucVu(head); break;
            case 6: timTheoHeSoVaPhongBan(head); break;
            case 7: sapXepTheoTen(head); break;
            case 8: inDanhSach(head); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
    huyDanhSach(head);
    return 0;
}