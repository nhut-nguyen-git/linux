# Giải thích nhanh chương trình:



# Cách biên dịch và chạy:
## Biên dịch:
make all
## Chạy chương trình:
bash
./example_program

# Ví dụ kết quả khi chạy:
Timer started. Press Ctrl+C to interrupt.
Timer: 1 seconds
Timer: 2 seconds
Timer: 3 seconds
Timer: 4 seconds
Timer: 5 seconds
Timer: 6 seconds
Timer: 7 seconds
Timer: 8 seconds
Timer: 9 seconds
Timer: 10 seconds
Reached 10 seconds. Exiting program.

## Câu hỏi: Điều gì xảy ra nếu không gọi lại alarm(1) trong hàm xử lý?
👉 Nếu không gọi alarm(1) trong hàm handle_sigalrm(), thì chương trình chỉ nhận tín hiệu SIGALRM đúng 1 lần duy nhất (sau 1 giây).
Sau đó, không có tín hiệu mới, nên pause() sẽ chờ mãi mãi và chương trình không đếm tiếp nữa.
Giải thích kỹ:
alarm(1) chỉ cài đồng hồ hẹn giờ một lần.
Khi đồng hồ kêu (SIGALRM), nếu bạn không cài lại alarm, thì không còn tín hiệu mới.
Vì thế chương trình sẽ đứng im sau dòng "Timer: 1 seconds".