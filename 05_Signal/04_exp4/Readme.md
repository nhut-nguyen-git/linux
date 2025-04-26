# Giải thích nhanh chương trình:

Thành phần	                        Ý nghĩa
signal(SIGTSTP, handle_sigtstp)	    Đăng ký hàm xử lý khi nhận SIGTSTP.
handle_sigtstp	                    Khi nhận SIGTSTP, in ra "SIGTSTP ignored", KHÔNG dừng chương trình.
pause()	                            Chờ tín hiệu đến. Không tốn CPU.
while (1)	                        Giữ chương trình chạy liên tục.

# Cách biên dịch và chạy:
## Biên dịch với thư viện realtime (-lrt):
make all
## Chạy chương trình:
bash
./example_program

Sau đó bấm Ctrl + Z, sẽ thấy chương trình không bị dừng, mà in ra:

Program is running. Press Ctrl+Z to test SIGTSTP.
^Z
SIGTSTP ignored


# Ví dụ kết quả khi chạy:
plaintext
Program is running. Press Ctrl+Z to test SIGTSTP.
^Z
SIGTSTP ignored

# Câu hỏi:
Nếu không xử lý tín hiệu SIGTSTP, chuyện gì xảy ra khi nhấn Ctrl+Z?

Trả lời:

Nếu KHÔNG bắt tín hiệu SIGTSTP, khi bạn nhấn Ctrl+Z, kernel sẽ tự động tạm dừng (suspend) tiến trình của bạn.
Bạn sẽ thấy shell in ra [1]+ Stopped ./ignore_sigtstp.
Muốn tiếp tục, phải dùng fg để đưa tiến trình về foreground và tiếp tục chạy.