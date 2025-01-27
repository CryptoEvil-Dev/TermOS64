#ifndef _EXT2_H_
#define _EXT2_H_

struct ext2_superblock{
	u32 s_inodes_count; 		// Общее количество инодов
	u32 s_blocks_count; 		// Общее количество блоков
	u32 s_r_blocks_count; 		// Количество резервных блоков
	u32 s_free_blocks_count; 	// Количество свободных блоков
	u32 s_free_inodes_count; 	// Количество свободных инодов
	u32 s_first_data_block; 	// Номер первого блока данных
	u32 s_log_block_size; 		// Размер блока в логарифмическом виде
	u32 s_log_frag_size; 		// Размер фрагмента в логарифмическом виде
	u32 s_blocks_per_group; 	// Количество блоков в группе
	u32 s_frags_per_group; 		// Количество фрагментов в группе
	u32 s_inodes_per_group; 	// Количество инодов в групе
	u32 s_mtime;			// Время последнего монтирования
	u32 s_wtime;			// Время последнего изменения
	u16 s_mnt_count;		// Счётчик монтирования
	u16 s_max_mnt_count;		// Максимальное количество монтирований
	u16 s_magic;			// Магическое число (должно быть 0xEF53)
	u16 s_state;			// Состояние файловой системы (чистая или грязная)
	u16 s_errors;			// Поведение при ошибках
	u16 s_minor_rev_level;		// Минимальная версия
	u32 s_lastcheck;		// Время последней проверки
	u32 s_checkinterval;		// Интервал между проверками
	u32 s_creator_os;		// Операционная система, создавшая файловую систему
	u32 s_rev_level;		// Версия файловой системы
	u16 s_def_resuid;		// UID по умолчанию для резервных блоков
	u16 s_def_resgid;		// GID по умолчанию для резервных блоков
	u32 s_first_ino;		// Номер первого инода (обычно 11)
	u16 s_inode_size;		// Размер инода в байтах
	u16 s_block_group_nr;		// Номер группы блоков
	u32 s_feature_compat;		// Совместимые функции
	u32 s_feature_incompat;		// Несовместимые функции
	u32 s_feature_ro_compat;	// Только для чтения функции
	u8  s_uuid[16];			// UUID файловой системы
	u8  s_volume_name[16];		// Имя тома
	u8  s_last_mounted[64];		// Последний путь монтирования
	u32 s_algorithm_usage_bitmap;	// Алгоритм использования
}

#endif
