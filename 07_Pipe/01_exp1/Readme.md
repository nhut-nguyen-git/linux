# 📚 Pipe Communication Between Parent and Child Process
## 1. Giải thích chương trình
Chương trình thực hiện giao tiếp giữa parent và child process bằng pipe trong C.

Các bước thực hiện:
### 1.Tạo Pipe

c
pipe(pipe_fd);

### 2.Tạo ra một mảng 2 phần tử pipe_fd[0] (để read) và pipe_fd[1] (để write).

Fork một tiến trình con


child_pid = fork();


child_pid > 0: Đây là tiến trình cha.

child_pid == 0: Đây là tiến trình con.

child_pid < 0: Có lỗi khi tạo tiến trình (thoát chương trình).

### 3.Tiến trình cha

Đóng đầu đọc (pipe_fd[0]).

Ghi thông điệp message vào đầu ghi (pipe_fd[1]).

In số byte đã gửi.

Đóng đầu ghi (pipe_fd[1]).

Chờ tiến trình con kết thúc (wait(NULL)).

### 4.Tiến trình con

Đóng đầu ghi (pipe_fd[1]).

Đọc thông điệp từ đầu đọc (pipe_fd[0]).

In số byte đã nhận và nội dung nhận được.

Đóng đầu đọc (pipe_fd[0]).

### 5.Kết thúc chương trình

## 2. Cách chạy chương trình
Các bước:

### 1.Biên dịch chương trình:

bash
make all

### 2.Chạy chương trình:

bash
./example_program

## 3. Kết quả chương trình thực hiện
Khi bạn chạy chương trình, bạn sẽ thấy output tương tự như sau:

plaintext
Parent process sent 28 bytes.
Child process received 28 bytes: Hello from parent process!

Giải thích:

"Parent process sent 28 bytes.": Tiến trình cha đã gửi 28 byte dữ liệu (bao gồm cả \0 null-terminator).

"Child process received 28 bytes: Hello from parent process!": Tiến trình con nhận được đúng dữ liệu đó và in ra màn hình.