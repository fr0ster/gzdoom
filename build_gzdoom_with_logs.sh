#!/bin/bash

# Скрипт для збірки GZDoom з детальним логуванням

# Змінні з шляхами
GZDOOM_DIR="/home/okyslytsia/prj/gzdoom"
INSTALL_DIR="$HOME/opt/doom"
ZMUSIC_DIR="$HOME/opt/ZMusic"
LOG_DIR="$GZDOOM_DIR/build_logs"

# Створюємо директорію для логів
mkdir -p "$LOG_DIR"

# Переходимо в директорію GZDoom
cd "$GZDOOM_DIR" || { echo "Помилка: не вдалося перейти в директорію $GZDOOM_DIR"; exit 1; }

echo "Починаємо збірку GZDoom з логуванням..."
echo "Директорія GZDoom: $GZDOOM_DIR"
echo "Директорія встановлення: $INSTALL_DIR"
echo "Директорія ZMusic: $ZMUSIC_DIR"
echo "Логи зберігаються в: $LOG_DIR"

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

# Конфігуруємо збірку з логуванням
echo "Конфігуруємо збірку CMake..."
cmake .. \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DZDOOM_OUTPUT_OLDSTYLE=ON \
    -DZMUSIC_INCLUDE_DIR="$ZMUSIC_DIR/include" \
    -DZMUSIC_LIBRARIES="$ZMUSIC_DIR/lib/libzmusic.so" \
    -DFORCE_INTERNAL_BZIP2=ON \
    -DFORCE_INTERNAL_ASMJIT=ON \
    -DCMAKE_CXX_FLAGS="-Wno-sign-compare -Wno-format" \
    2>&1 | tee "$LOG_DIR/cmake_config.log"

# Перевіряємо успішність конфігурації
if [ ${PIPESTATUS[0]} -ne 0 ]; then
    echo "Помилка під час конфігурації CMake! Дивіться лог: $LOG_DIR/cmake_config.log"
    exit 1
fi

# Збираємо з детальним логуванням
echo "Починаємо збірку..."
make -j$(nproc) VERBOSE=1 2>&1 | tee "$LOG_DIR/build.log"

# Перевіряємо успішність збірки
if [ ${PIPESTATUS[0]} -ne 0 ]; then
    echo "Помилка під час збірки! Дивіться лог: $LOG_DIR/build.log"
    
    # Витягуємо останні помилки для швидкого аналізу
    echo "=== ОСТАННІ ПОМИЛКИ ===" > "$LOG_DIR/errors_summary.log"
    tail -50 "$LOG_DIR/build.log" | grep -i "error\|fatal\|undefined" >> "$LOG_DIR/errors_summary.log"
    
    echo "Короткий звіт про помилки збережено в: $LOG_DIR/errors_summary.log"
    cat "$LOG_DIR/errors_summary.log"
    exit 1
fi

# Встановлюємо
echo "Встановлюємо в $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"

# Перевіряємо права доступу до директорії встановлення
if [ -w "$INSTALL_DIR" ]; then
    # Якщо є права на запис, встановлюємо без sudo
    make install 2>&1 | tee "$LOG_DIR/install.log"
    INSTALL_RESULT=${PIPESTATUS[0]}
else
    # Якщо немає прав на запис, використовуємо sudo
    echo "Для встановлення потрібні права адміністратора. Використовуємо sudo..."
    sudo make install 2>&1 | tee "$LOG_DIR/install.log"
    INSTALL_RESULT=${PIPESTATUS[0]}
fi

if [ ${PIPESTATUS[0]} -eq 0 ]; then
    echo "\nУспішно зібрано та встановлено GZDoom в $INSTALL_DIR"
    echo "Ви можете запустити GZDoom командою: $INSTALL_DIR/bin/gzdoom"
    echo "Логи збережено в: $LOG_DIR"
else
    echo "\nПомилка під час встановлення! Дивіться лог: $LOG_DIR/install.log"
    exit 1
fi
