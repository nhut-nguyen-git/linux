# Giải thích nhanh chương trình:

## 1.Parent Process:

Tạo message queue (nếu chưa có).

Gửi chuỗi ký tự nhập từ bàn phím vào queue.

## 2.Child 1:

Nhận message từ queue.

Chuyển toàn bộ thành chữ hoa.

Gửi lại message đã chuyển về queue.

## 3.Child 2:

Nhận message đã chuyển thành chữ hoa từ queue.

In ra màn hình.

## 4.Cuối chương trình:

Các tiến trình đều đóng message queue.

Parent xoá message queue (mq_unlink()).

# Cách biên dịch và chạy:
## Biên dịch với thư viện realtime (-lrt):
make all
## Chạy chương trình:
bash
./example_program

# Ví dụ kết quả khi chạy:

Parent process: Enter a message to send: Hello
Child 1 received: Hello
Child 2 received and prints: HELLO
Parent process: All child processes have finished.

# Ghi chú quan trọng:
POSIX message queues yêu cầu thêm -lrt khi compile (-lrt = real-time library).
Message queue name bắt buộc phải bắt đầu bằng dấu / (ví dụ: /my_message_queue).
Đừng quên mq_unlink() để tránh "rác" tồn đọng trong hệ thống!