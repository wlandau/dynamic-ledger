CC=gcc
CCFLAGS=-c -Wall -pedantic -Iinclude/
LDFLAGS=-lm

SRCDIR=src/
OBJDIR=obj/
BINDIR=bin/

BINNAME=ledger-txt
BIN=$(BINDIR)$(BINNAME)

DEP=alloc_text_content bad_input_file bad_output_file check_legal_double
DEP+=check_legal_double_modify_entry condense condense_and_print condense_str
DEP+=contains_tabs free_for_retotal free_ledger get_color
DEP+=get_ledger_from_filename get_ledger_from_stream get_ledger_from_string get_names
DEP+=get_text_content_from_stream get_text_content_from_string get_totals insert_row
DEP+=insert_row_str is_space legal_amounts modify_entry
DEP+=modify_entry_str new_ledger print_ledger_to_stream print_ledger_to_string
DEP+=print_ledger_verbose print_summary_to_stream print_summary_to_string qcmp
DEP+=remove_row remove_row_str rename_bank rename_bank_str
DEP+=rename_credit rename_credit_str rename_partition rename_partition_str
DEP+=standalone str_equal str_strip summarize_file_to_stream
DEP+=trim_ledger trim_ledger_str unique usage

OBJ=$(foreach name, $(DEP), $(OBJDIR)$(name).o)

all: $(BIN)
	
$(BIN): $(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN) 

$(OBJDIR)%.o: $(SRCDIR)%.c dirs
	$(CC) $(CCFLAGS) $< -o $@ 

.INTERMEDIATE: dirs

dirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
