#include <stdio.h>
#include <stdlib.h>
#include <capstone/capstone.h>
#include "file_utils.h"
#include "disassemble.h"

int disassemble_file(const char *filename) {
  csh handle;
  cs_insn *insn;
  size_t count, i;
  size_t code_size;
  unsigned char *code;
  cs_err err;

  // Initialize Capstone for x86-64
  err = cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
  if (err != CS_ERR_OK) {
    fprintf(stderr, "Failed to initialize Capstone: %s\n", cs_strerror(err));
    return 1;
  }

  // Read bytes from the file
  code = read_file(filename, &code_size);
  if (!code) {
    cs_close(&handle);
    return 1;
  }

  // Disassemble the code
  count = cs_disasm(handle, code, code_size, 0x1000, 0, &insn);
  if (count > 0) {
    for (i = 0; i < count; i++) {
      printf("0x%lx:\t%s\t%s\n", insn[i].address, insn[i].mnemonic, insn[i].op_str);
    }
    cs_free(insn, count);
    } else {
        printf("Disassembly failed\n");
    }

  // Cleanup
  free(code);
  cs_close(&handle);

  return 0;
}
