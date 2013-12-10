CC=gcc
CCFLAGS=-c -Wall -pedantic -Iinclude/
LDFLAGS=-lm

SRCDIR=src/
OBJDIR=obj/
BIN=ledger

DEP=alloc_entries 
DEP+=bad_input_file 
DEP+=bad_output_file
DEP+=check_legal_double
DEP+=condense 
DEP+=condense_and_print
DEP+=condense_str
DEP+=contains_column_delim
DEP+=contains_row_delim
DEP+=free_for_retotal 
DEP+=free_ledger get_color
DEP+=get_entries_from_stream 
DEP+=get_entries_from_string 
DEP+=get_ledger_from_filename 
DEP+=get_ledger_from_stream  
DEP+=get_ledger_from_string 
DEP+=get_names get_totals 
DEP+=insert_row
DEP+=insert_row_str 
DEP+=is_space 
DEP+=legal_amounts 
DEP+=modify_entry
DEP+=modify_entry_str 
DEP+=new_ledger
DEP+=print_ledger_to_stream 
DEP+=print_ledger_to_string
DEP+=print_ledger_verbose
DEP+=print_summary_to_stream
DEP+=print_summary_to_string 
DEP+=qcmp
DEP+=remove_row 
DEP+=remove_row_str
DEP+=rename_bank
DEP+=rename_bank_str
DEP+=rename_credit 
DEP+=rename_credit_str 
DEP+=rename_partition 
DEP+=rename_partition_str
DEP+=standalone 
DEP+=str_equal 
DEP+=str_strip 
DEP+=summarize_file_to_stream
DEP+=trim_ledger 
DEP+=trim_ledger_str 
DEP+=unique 
DEP+=usage
DEP+=which

OBJ=$(foreach name, $(DEP), $(OBJDIR)$(name).o)

all: $(BIN)
	
$(BIN): $(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN) 

$(OBJDIR)%.o: $(SRCDIR)%.c dirs
	$(CC) $(CCFLAGS) $< -o $@ 

.INTERMEDIATE: dirs

dirs:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f  $(BIN)
