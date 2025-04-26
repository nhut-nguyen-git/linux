# Giải thích nhanh chương trình:

## signal(SIGINT, handle_sigint);:
Đăng ký handle_sigint làm hàm xử lý tín hiệu SIGINT.
Nhưng trên một số hệ thống Unix cổ (Linux cũng vậy), sau khi bắt một tín hiệu thì signal() tự động reset handler về mặc định (SIG_DFL).

## Vì vậy, trong chính hàm handle_sigint(), mình gọi lại signal(SIGINT, handle_sigint); để đăng ký lại handler mỗi lần nhận tín hiệu.
➔ Điều này đảm bảo rằng mỗi lần nhấn Ctrl+C thì chương trình vẫn bắt được, không bị thoát sớm.

## (void)sig;:
Để tránh warning "unused parameter 'sig'" do trong hàm handle_sigint() không cần dùng tham số sig.

# Cách biên dịch và chạy:
## Biên dịch 
make all
## Chạy chương trình:
bash
./example_program

# Ví dụ kết quả khi chạy:
plaintext
Program is running. Press Ctrl+C to send SIGINT.
^C
SIGINT received (1/3)
^C
SIGINT received (2/3)
^C
SIGINT received (3/3)
Received SIGINT 3 times. Exiting program.
