#include "hash.h"
#include <ctype.h>
#include <stdio.h>

#define HASH_BUFFER_SIZE 0x500
static unsigned long hash_buffer[HASH_BUFFER_SIZE];
static bool hash_buffer_created;

int init_hash_buffer()
{
    unsigned long dwSeed = 0x00100001;
    unsigned long index1 = 0;
    unsigned long index2 = 0;
    int   i;

    // Initialize the decryption buffer.
    // Do nothing if already done.
    if(hash_buffer_created == false)
    {
        for(index1 = 0; index1 < 0x100; index1++)
        {
            for(index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
            {
                unsigned long temp1, temp2;

                dwSeed = (dwSeed * 125 + 3) % 0x2AAAAB;
                temp1  = (dwSeed & 0xFFFF) << 0x10;

                dwSeed = (dwSeed * 125 + 3) % 0x2AAAAB;
                temp2  = (dwSeed & 0xFFFF);

                hash_buffer[index2] = (temp1 | temp2);
            }
        }
        hash_buffer_created = false;
    }
    return 0;
}

Hash* get_hash_entry(Hash* table, const char* key, unsigned long table_size)
{
  Hash* hashEnd = table + table_size;
  Hash* hash0;
  Hash* hash;
  unsigned long index = (unsigned long)key;
  unsigned long keyA;
  unsigned long keyB;

  if(index <= table_size)
  {
    for(hash = table;hash<hashEnd;hash++)
    {
      if(hash->index == index)
        return hash;
    }
    return NULL;
  }

  index = hash_index(table_size,key);
  keyA = hash_keyA(key);
  keyB = hash_keyB(key);

  hash = hash0 = table + index;
  while(hash->index != HASH_ENTRY_FREE)
  {
    if(hash->keyA == keyA && hash->keyB == keyB && hash->index != HASH_ENTRY_DELETED)
      return hash;
    if(++hash >= hashEnd)
      hash = table;
    if(hash == hash0)
      break;
  }

  return NULL;
}

unsigned long hash_index(unsigned long table_size, const char* key)
{
  unsigned char* ukey = (unsigned char*) key;
  unsigned long dwSeed1 = 0x7FED7FED;
  unsigned long dwSeed2 = 0xEEEEEEEE;
  unsigned long ch;

  while(ukey !=0 )
  {
    ch = toupper(*key++);
    dwSeed1 = hash_buffer[0x000 + ch] ^ (dwSeed1 + dwSeed2);
    dwSeed2 = ch + dwSeed1 + dwSeed2 + (dwSeed2 << 5) + 3;
  }
  return (dwSeed1 & (table_size - 1));
}

unsigned long hash_keyA(const char* key)
{
  unsigned char* ukey = (unsigned char*) key;
  unsigned long dwSeed1 = 0x7FED7FED;
  unsigned long dwSeed2 = 0xEEEEEEEE;
  unsigned long ch;

  while(ukey !=0 )
  {
    ch = toupper(*key++);
    dwSeed1 = hash_buffer[0x100 + ch] ^ (dwSeed1 + dwSeed2);
    dwSeed2 = ch + dwSeed1 + dwSeed2 + (dwSeed2 << 5) + 3;
  }
  return dwSeed1;
}

unsigned long hash_keyB(const char* key)
{
  unsigned char* ukey = (unsigned char*) key;
  unsigned long dwSeed1 = 0x7FED7FED;
  unsigned long dwSeed2 = 0xEEEEEEEE;
  unsigned long ch;

  while(ukey !=0 )
  {
    ch = toupper(*key++);
    dwSeed1 = hash_buffer[0x200 + ch] ^ (dwSeed1 + dwSeed2);
    dwSeed2 = ch + dwSeed1 + dwSeed2 + (dwSeed2 << 5) + 3;
  }
  return dwSeed1;
}
