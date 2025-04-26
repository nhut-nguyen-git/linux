# Giải thích chương trình:

Thành phần	Giải thích
pipe(pipe_fd)	Tạo một pipe gồm hai đầu: pipe_fd[0] để đọc và pipe_fd[1] để ghi
fork()	Tạo ra một tiến trình con
Tiến trình cha	Gửi chuỗi "This is a sample string." vào pipe
Tiến trình con	Nhận chuỗi từ pipe, đếm số ký tự bằng strlen(), và in kết quả ra màn hình
Quản lý pipe	Đóng đúng các đầu đọc/ghi để tránh deadlock
# Cách chạy chương trình:
Biên dịch:

bash
make all
Chạy:

bash

./example_program

# Kết quả ví dụ:
plaintext
Parent process sent 24 bytes: This is a sample string.
Child process received 24 bytes: This is a sample string.
Child process counted 24 characters.