typedef struct memblock_s
{
    int size; // размер всего блока памяти, включая заголовок
    int used; // если равен 0 то блок свободен
    int id; // всегда будет равно 0x1d4a11 для проверки целостности
    struct memblock_s *next;
    struct memblock_s *prev;
} memblock_t;

/*
 * 
*/
void *Z_Malloc(int size);

/*
 * Инициализировать аллокацию памяти
 * @param buf Буфер который будут использовать аллокаторы
 * @param size Размер буфера
*/
void Memory_Init(void *buf, int size);
