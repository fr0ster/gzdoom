#!/bin/bash

# Змінні з шляхами
GZDOOM_DIR="/home/okyslytsia/prj/gzdoom"
INSTALL_DIR="$HOME/opt/doom"
ZMUSIC_DIR="$HOME/opt/ZMusic"

# Переходимо в директорію GZDoom
cd "$GZDOOM_DIR" || { echo "Помилка: не вдалося перейти в директорію $GZDOOM_DIR"; exit 1; }

echo "Починаємо збірку GZDoom..."
echo "Директорія GZDoom: $GZDOOM_DIR"
echo "Директорія встановлення: $INSTALL_DIR"
echo "Директорія ZMusic: $ZMUSIC_DIR"

# Перевіряємо наявність ZMusic
if [ ! -d "$ZMUSIC_DIR" ]; then
    echo "Помилка: директорія ZMusic не знайдена в $ZMUSIC_DIR"
    echo "Будь ласка, встановіть ZMusic спочатку"
    exit 1
fi

# Створюємо директорію для збірки
echo "Створюємо директорію для збірки..."
rm -rf build
mkdir -p build
cd build || { echo "Помилка: не вдалося створити/перейти в директорію build"; exit 1; }

# Конфігуруємо збірку
echo "Конфігуруємо збірку CMake..."
cmake .. \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DZDOOM_OUTPUT_OLDSTYLE=ON \
    -DZMUSIC_INCLUDE_DIR="$ZMUSIC_DIR/include" \
    -DZMUSIC_LIBRARIES="$ZMUSIC_DIR/lib/libzmusic.so" \
    -DFORCE_INTERNAL_BZIP2=ON \
    -DFORCE_INTERNAL_ASMJIT=ON \
    -DCMAKE_CXX_FLAGS="-Wno-sign-compare -Wno-format"

# Перевіряємо успішність конфігурації
if [ $? -ne 0 ]; then
    echo "Помилка під час конфігурації CMake!"
    exit 1
fi

# Збираємо
echo "Починаємо збірку..."
make -j$(nproc)

# Перевіряємо успішність збірки
if [ $? -ne 0 ]; then
    echo "Помилка під час збірки!"
    exit 1
fi

# Встановлюємо
echo "Встановлюємо в $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"
make install

if [ $? -eq 0 ]; then
    echo "\nУспішно зібрано та встановлено GZDoom в $INSTALL_DIR"
    echo "Ви можете запустити GZDoom командою: $INSTALL_DIR/bin/gzdoom"
else
    echo "\nПомилка під час встановлення!"
    exit 1
fi
