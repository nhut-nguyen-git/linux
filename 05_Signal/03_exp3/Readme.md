# Giải thích nhanh chương trình:

Giải thích chương trình C:

## #include các thư viện cần thiết:

stdio.h: Cho các hàm nhập/xuất chuẩn như printf.
stdlib.h: Cho các hàm tiện ích chung như exit.
unistd.h: Cho các системный вызов (system calls) như fork, pipe, close, read, write, sleep.
signal.h: Cho các hàm liên quan đến xử lý tín hiệu như signal, kill.
sys/types.h: Định nghĩa các kiểu dữ liệu hệ thống như pid_t.
sys/wait.h: Cho hàm wait để chờ process con kết thúc.

## signal_handler(int signum):

Đây là hàm xử lý tín hiệu. Khi process con nhận được tín hiệu, hàm này sẽ được gọi.
signum là số hiệu của tín hiệu đã nhận được. Chúng ta kiểm tra nếu nó là SIGUSR1 và in ra thông báo.

## main():

Tạo pipe: pipe(pipefd) tạo một pipe. pipefd[0] là đầu đọc và pipefd[1] là đầu ghi. Pipe được sử dụng để đồng bộ hóa giữa process cha và con.
Tạo process con: child_pid = fork() tạo một process con.
Nếu fork() trả về -1, có lỗi xảy ra.
Nếu fork() trả về 0, đây là mã của process con.
Nếu fork() trả về một giá trị dương, đây là PID của process con trong process cha.
Trong process con (child_pid == 0):
Đóng đầu ghi của pipe (close(pipefd[1])) vì process con chỉ đọc.
Đăng ký hàm xử lý tín hiệu signal_handler cho tín hiệu SIGUSR1 bằng signal(SIGUSR1, signal_handler).
In thông báo cho biết process con đã sẵn sàng.
Đọc một byte từ pipe (read(pipefd[0], &ready_signal, 1)). Process con sẽ bị block cho đến khi process cha ghi dữ liệu vào pipe, đảm bảo process cha đã sẵn sàng gửi tín hiệu.
Đóng đầu đọc của pipe (close(pipefd[0])).
Vòng lặp while(1) để process con tiếp tục chạy và chờ tín hiệu.
exit(EXIT_SUCCESS) để kết thúc process con một cách bình thường (trong trường hợp có điều kiện kết thúc khác).
Trong process cha (child_pid > 0):
Đóng đầu đọc của pipe (close(pipefd[0])) vì process cha chỉ ghi.
In thông báo cho biết process cha đã tạo process con.
Ghi một byte vào pipe (write(pipefd[1], "1", 1)) để báo cho process con biết process cha đã sẵn sàng gửi tín hiệu.
Đóng đầu ghi của pipe (close(pipefd[1])).
Vòng lặp for chạy 5 lần:
In thông báo trước khi gửi tín hiệu.
Gửi tín hiệu SIGUSR1 đến process con bằng kill(child_pid, SIGUSR1).
sleep(2) để tạm dừng 2 giây.
In thông báo sau khi gửi 5 tín hiệu.
wait(NULL) để chờ process con kết thúc trước khi process cha kết thúc. Điều này giúp tránh tình trạng process con trở thành zombie process.
exit(EXIT_SUCCESS) để kết thúc process cha một cách bình thường.
return 0; để báo hiệu chương trình chính kết thúc thành công.

# Cách biên dịch và chạy:
## Biên dịch :
make all
## Chạy chương trình:
bash
./example_program

# Ví dụ kết quả khi chạy:
plaintext
Parent process (PID: 4315) created child process (PID: 4316).
Parent process (PID: 4315) is sending SIGUSR1 signal (count: 1)...
Parent process (PID: 4315) is sending SIGUSR1 signal (count: 2)...
Parent process (PID: 4315) is sending SIGUSR1 signal (count: 3)...
Parent process (PID: 4315) is sending SIGUSR1 signal (count: 4)...
Parent process (PID: 4315) is sending SIGUSR1 signal (count: 5)...
Parent process (PID: 4315) has sent SIGUSR1 signal 5 times. Terminating.


