// https://osdev.fandom.com/ru/wiki/Файловая_система_Ext2
#ifndef _EXT2_H_
#define _EXT2_H_

#include "../boot/types.h"

#define EXT2_N_BLOCKS 2048 // Не факт, надо будт разобраться!

// Операционная система создавшая файловую систему
#define OS_LINUX 		0
#define OS_GNU_HURD 	1
#define OS_MASIX 		2
#define OS_FREEBSD		3
#define OS_OTHER		4
// Типы файлов
#define FT_FIFO			0x1
#define FT_SYMLINK		0x2
#define FT_DIR			0x4
#define FT_BLOCKDEV		0x6
#define FT_REGFILE		0x8
#define FT_LINK			0xA
#define FT_UNIXSOCKET	0xC


struct ext2_super_block {
	u32   s_inodes_count;        /*  Количество индексных дескрипторов в ФС */
	u32   s_blocks_count;        /*  Количество блоков в ФС */
	u32   s_r_blocks_count;      /*  Количество зарезервированых блоков */
	u32   s_free_blocks_count;   /*  Количество свободных блоков */
	u32   s_free_inodes_count;   /*  Количество свободных индексных дескрипторов */
	u32   s_first_data_block;    /*  Номер данного блока */
	u32   s_log_block_size;      /*  log2(размер блока)-10 */
	s32   s_log_frag_size;       /*  log2(размер фрагмента)-10 */
	u32   s_blocks_per_group;    /*  #  Кол-во блоков в группе */
	u32   s_frags_per_group;     /*  #  Кол-во фрагментов в группе */
	u32   s_inodes_per_group;    /*  #  Кол-во индексных дескрипторов в группе */
	u32   s_mtime;               /*  Время последнего монтирования в POSIX времени */
	u32   s_wtime;               /*  Время последней записи в POSIX времени */
	u16   s_mnt_count;           
	s16   s_max_mnt_count;       
	u16   s_errors;              /*  Код ошибки(см.ниже) */
	u16   s_pad;
	u32   s_lastcheck;           /*  POSIX время последней проверки */
	u32   s_checkinterval;       /*  POSIX время между принудительными проверками */
	u32   s_creator_os;          /*  ID ОС (см. ниже)  */
	u32   s_rev_level;           /*  Версия */
	u16   s_def_resuid;          /*  UserID, могущий использовать зар. блоки */
	u16   s_def_resgid;          /*  GroupID, могущий использовать зар. блоки */
	u32   s_reserved[235];       /*  Зарезервировано */
};
struct ext2_group_desc
{
	u32 bg_block_bitmap;        /*  Номер блока в битовой карте*/
	u32 bg_inode_bitmap;        /*  Дескриптор блока в битовой карте */
	u32 bg_inode_table;         /*  Номер блока в таблице дескрипторов */
	u16 bg_free_blocks_count;   /*  Свободно блоков */
	u16 bg_free_inodes_count;   /*  Свободно индексных дескрипторов */
	u16 bg_used_dirs_count;     /*  Количество директорий */
	u16 bg_pad;
	u32 bg_reserved[3];
};

struct ext2_inode {
	u16	i_mode;		/* Тип файла и права доступа (см.ниже) */
	u16	i_uid;		/* UserID */
	u32	i_size;		/* Размер в байтах */
	u32	i_atime;	/* POSIX время последнего обращения к файлу */
	u32	i_ctime;	/* POSIX время создания */
	u32	i_mtime;	/* POSIX время последней модификации */
	u32	i_dtime;	/* POSIX время удаления */
	u16	i_gid;		/* GroupID */
	u16	i_links_count;	/* Кол-во ссылок на дескриптор */
 	u32	i_blocks;	/* Кол-во секторов (не блоки!) */
	u32	i_flags;	/* Флаг (см.ниже) */
	union {
		struct {
			u32  l_i_reserved1; /* Зарезервировано */
		} linux1;
		struct {
			 u32  h_i_translator; /* ??? */
		} hurd1;
		struct {
			u32  m_i_reserved1; /* Зарезервировано */
		} masix1;
	 } osd1;		
	u32	i_block[EXT2_N_BLOCKS];/* Указатели на блок */
	u32	i_generation;	/* Версия файла (для NFS) */
	u32	i_file_acl;	/* Доп. аттрибуты файла */
	u32	i_dir_acl;	/* Доп. аттрибуты директории */
	u32	i_faddr;	/* Адрес фрагмента */
	union {
		struct {
			u8	l_i_frag;	/* Номер фрагмента */
			u8	l_i_fsize;	/* Размер фрагмента */
			u16	i_pad1;         /* Зарезервировано */
			u16	l_i_uid_high;	/* 16 старших битов UserID */
			u16	l_i_gid_high;	/* 16 старших битов GroupID */
			u32	l_i_reserved2;  /* Зарезервировано */
		} linux2; /* LINUX */
		struct {
			u8	h_i_frag;	/* Номер фрагмента */
			u8	h_i_fsize;	/* Размер фрагмента */
			u16	h_i_mode_high;  /* 16 старших битов T&P */
			u16	h_i_uid_high;   /* 16 старших битов UserID */
			u16	h_i_gid_high;   /* 16 старших битов GroupID */
			u32	h_i_author;     /* UserID или автор */
		} hurd2; /* GNU HURD */
		struct {
			u8	m_i_frag;	/* Номер фрагмента */
			u8	m_i_fsize;      /* Размер фрагмента */
			u16	m_pad1;         /* Зарезервировано */
			u32	m_i_reserved2[2]; /* Зарезервировано */
		} masix2; /* MASIX */
	} osd2;				/* Специфичные значения */
};

/* Read */
// Прочитать суперблок, что бы получить информацию о размере блоков, количество инодов и другие параметры
// Разделить указаный путь на отдельные компоненты /home/user/file.txt -> ['home','user','file.txt']
// Найти корневой каталог, что бы получить информацию о его блоках
// Итерации по компонентам пути:
// 		Для каждой компоненты пути:
//			1. Прочитать блок каталога, связанные с текущим инодом.
//			2. Найти инод, соответствующий имени текущей компоненты
//			3. Если компонент не найден, завершить процесс с ошибкой
//			4. Если компонент найден, обновить текущий инод на найденный
//		Чтение данных файла:
//			После того как инод файла найден, прочитать его блоки
//			Использовать указатели на блоки из инода для чтения данных файла
//		Вывод данных:
//			Вывести или обработать данные, считанные из файла

ext2_super_block ReadSuperblock(){
	ext2_super_block ext;
	
	return ext;
	
}
ext2_inode ReadInode(){
	ext2_inode inode;
	return inode;
}
ext2_group_desc ReadGroup(){
	ext2_group_desc group;

	return group;
}

#endif