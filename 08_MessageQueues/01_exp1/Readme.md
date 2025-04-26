# Giải thích nhanh chương trình:

Thành phần	    Giải thích
mq_open()	    Tạo hoặc mở message queue
mq_send()	    Gửi tin nhắn từ tiến trình cha
mq_receive()	Nhận tin nhắn từ tiến trình con
mq_close()	    Đóng message queue sau khi sử dụng
mq_unlink()	    Xóa message queue khỏi hệ thống

# Cách biên dịch và chạy:
## Biên dịch với thư viện realtime (-lrt):
make all
## Chạy chương trình:
bash
./example_program

# Ví dụ kết quả khi chạy:
plaintext
Parent process sent message: Hello from parent!
Child process received message: Hello from parent!

# Ghi chú quan trọng:
POSIX message queues yêu cầu thêm -lrt khi compile (-lrt = real-time library).
Message queue name bắt buộc phải bắt đầu bằng dấu / (ví dụ: /my_message_queue).
Đừng quên mq_unlink() để tránh "rác" tồn đọng trong hệ thống!