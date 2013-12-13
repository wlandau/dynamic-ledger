CC=gcc
CCFLAGS=-c -Wall -pedantic -Iinclude/
LDFLAGS=-lm

SRCDIR=src/
OBJDIR=obj/
BIN=ledger

DEP=alloc_entries 
DEP+=alloc_totals
DEP+=col_delim_char
DEP+=col_delim_str
DEP+=color
DEP+=condense 
DEP+=condense_and_print
DEP+=condense_str
DEP+=free_for_retotal 
DEP+=free_ledger
DEP+=get_entries_from_filename
DEP+=get_entries_from_stream 
DEP+=get_entries_from_string 
DEP+=get_ledger_from_filename 
DEP+=get_ledger_from_stream  
DEP+=get_ledger_from_string 
DEP+=get_names get_totals 
DEP+=input_file 
DEP+=insert_row
DEP+=insert_row_str 
DEP+=legal_amounts 
DEP+=legal_double
DEP+=legal_status_code
DEP+=legal_status_codes
DEP+=modify_entry
DEP+=modify_entry_str 
DEP+=new_ledger
DEP+=output_file
DEP+=parse_char
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
DEP+=row_delim_char
DEP+=row_delim_str
DEP+=space 
DEP+=standalone 
DEP+=str_equal 
DEP+=str_strip
DEP+=strip_ledger 
DEP+=summarize_file_to_stream
DEP+=trim_ledger 
DEP+=trim_ledger_str 
DEP+=unique 
DEP+=usage
DEP+=which
DEP+=which_bank_total
DEP+=which_credit_total

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
