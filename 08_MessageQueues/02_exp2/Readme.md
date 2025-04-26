## Mô tả

Chương trình này minh họa **giao tiếp liên tiến trình (IPC)** bằng cách sử dụng **POSIX Message Queue**.  
Nó tạo hai hàng đợi tin nhắn để thực hiện giao tiếp hai chiều giữa tiến trình cha và tiến trình con:

- **Hàng đợi 1:** Cha → Con (gửi chuỗi ký tự)
- **Hàng đợi 2:** Con → Cha (gửi kết quả đếm số ký tự)

---

## 🏗 Quy trình hoạt động

1. Tiến trình cha gửi một chuỗi ký tự cho tiến trình con thông qua hàng đợi tin nhắn.
2. Tiến trình con đọc tin nhắn, đếm số ký tự, và gửi kết quả đếm về lại cho tiến trình cha qua một hàng đợi khác.
3. Tiến trình cha nhận kết quả và in ra màn hình.

---

## 🔧 Cách biên dịch chương trình

Bạn cần biên dịch chương trình và **liên kết với thư viện -lrt

```bash
make all
```
## ách chạy chương trình
```bash
./example_program
```

## Ví dụ kết quả khi chạy

```bash
Parent process sent message: Hello from parent to child!
Child process received message: Hello from parent to child!
Parent process received character count: 27
```

## 📌 Lưu ý
POSIX Message Queue yêu cầu hệ thống hỗ trợ mở rộng real-time (librt).

Luôn xoá (unlink) các hàng đợi tin nhắn sau khi sử dụng để tránh rò rỉ tài nguyên hệ thống.

Tên hàng đợi tin nhắn phải bắt đầu bằng dấu / và phải đảm bảo duy nhất trong hệ thống.

Chương trình đã bao gồm kiểm tra lỗi khi tạo, gửi, và nhận tin nhắn.