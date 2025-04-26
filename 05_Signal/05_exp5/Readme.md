# Giải thích nhanh chương trình:

- Nhấn `Ctrl+C` (SIGINT) ➔ In ra "SIGINT received".
- Gửi `SIGTERM` (`kill -15 <PID>`) ➔ Thoát chương trình sạch sẽ.
- Người dùng có thể nhập liệu song song.


# Cách biên dịch và chạy:
## Biên dịch :
make all
## Chạy chương trình:
bash
./example_program

Gõ chữ bất kỳ ➔ chương trình đọc và in lại.

Nhấn Ctrl+C ➔ chương trình không thoát, chỉ in ra thông báo.

Gửi SIGTERM từ terminal khác:

# Ví dụ kết quả khi chạy:

Program started. Type something or press Ctrl+C to send SIGINT.
Send SIGTERM to terminate the program (e.g., `kill -15 <pid>`).

hello world
You typed: hello world

abc xyz
You typed: abc xyz

# (Bạn nhấn Ctrl+C ở đây)
^C
SIGINT received.

# Bạn tiếp tục nhập
testing 123
You typed: testing 123

# (Ở terminal khác, bạn gửi lệnh:)
$ kill -15 <PID>

# Trên màn hình chương trình chính:
SIGTERM received. Exiting...

