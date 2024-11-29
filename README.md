# CS160-chess-project


**Build command:**

```
Just tested for windows. Not sure for other OS
click build.bat and wait for the magic 
File .exe nằm trong folder build
```

# NeetChessCS160

Giải thích nhanh code:

```
sử dụng 2 thư viện ngoài là raylib.h và virgo.h
```

Các Scene: Title Scene, Game Scene
- Title Scene
  - Mode Title: chọn mode game và độ khó
  - Load Title: load từ game đã lưu từ trước
  - Options Title: bật settings
- Game Scene
  - Base Game: vẽ background cho các gameScene khác
  - Main Game: dùng để chơi, tương tác chính
  - Pause Game: dẫn ra màn hình phụ có các nút chọn Save, Load, Options
  - End Game: render màn hình khi cờ vua kết thúc 

Các file chính hoạt động:
- Main: bật window và audio device.
- Properties: chứa, screenSize, assets, sounds, cursorMode, save files và settings liên quan đến chúng
- Game: dùng để tải thông tin ván game hiện tại, bao gồm tiến trình, saveload, và kết thúc
  - Renderer: dùng để hiển thị ván cờ
  - agents/: chứa AI
    - Random (easy): hell elo
    - AlphaBeta (): depth 4, sortDepth 2
    - SearchTree (medium): depth 3
    - Bitboard (hard): depth 6
  - Board: tải tiến trình game hiện tại, bao gồm thông tin mỗi con cờ và nước đi mới nhất
