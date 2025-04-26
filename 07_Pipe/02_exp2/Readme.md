# Giải thích chi tiết:
## 1. Pipe:
Pipe 1 (pipe1_fd): Dùng để giao tiếp từ tiến trình cha đến tiến trình con 1.

Pipe 2 (pipe2_fd): Dùng để giao tiếp từ tiến trình con 1 đến tiến trình con 2.

## 2. Các bước thực hiện:
Tiến trình cha tạo và mở hai pipe, sau đó gửi thông điệp đến Tiến trình con 1 qua Pipe 1.

Tiến trình con 1 nhận thông điệp từ Pipe 1, thay đổi nội dung (thêm chuỗi vào cuối) và gửi kết quả đến Tiến trình con 2 qua Pipe 2.

Tiến trình con 2 nhận thông điệp từ Pipe 2 và in nó ra màn hình.

## 3. Quản lý tài nguyên:
Đảm bảo mỗi tiến trình đóng đúng các đầu pipe không sử dụng để tránh deadlock.

Sau khi write() hoặc read() xong, cần phải đóng các đầu pipe tương ứng.

## 4. Quản lý tiến trình:
Tiến trình cha fork hai lần: một lần cho Tiến trình con 1 và một lần cho Tiến trình con 2.

wait() được sử dụng để đảm bảo tiến trình cha chờ các tiến trình con kết thúc.

# Cách chạy chương trình:
Các bước:
Biên dịch chương trình:

bash
make all

Chạy chương trình:
bash
./example_program

# Kết quả thực hiện chương trình:
Khi chạy chương trình, bạn sẽ thấy output tương tự như sau:

plaintext
Parent process sent 19 bytes: Hello from parent!
Child 1 received 19 bytes: Hello from parent!
Child 1 sent 53 bytes: Hello from parent! And this is from child 1!
Child 2 received 53 bytes: Hello from parent! And this is from child 1!