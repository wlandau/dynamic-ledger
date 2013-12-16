CC=gcc
CCFLAGS=-c -Wall -pedantic -Iinclude/ 

SRCDIR=src/
OBJDIR=obj/
TESTDIR=tests/
TUTORIALDIR=tutorial/
BIN=ledger

DEP=main
DEP+=alloc_entries 
DEP+=alloc_totals
DEP+=clean
DEP+=col_delim_char
DEP+=col_delim_str
DEP+=color
DEP+=condense 
DEP+=copy_ledger
DEP+=edit_entry
DEP+=edit_row
DEP+=filled_partitions
DEP+=free_for_retotal 
DEP+=free_ledger
DEP+=get_entries_from_filename
DEP+=get_entries_from_stream 
DEP+=get_entries_from_string 
DEP+=get_ledger
DEP+=get_names 
DEP+=get_totals 
DEP+=input_file 
DEP+=insert_rows
DEP+=legal_amounts 
DEP+=legal_double
DEP+=legal_status_code
DEP+=legal_status_codes
DEP+=locked
DEP+=move_rows
DEP+=new_ledger
DEP+=output_file
DEP+=parse_char
DEP+=permute_rows
DEP+=print_ledger_to_filename
DEP+=print_ledger_to_stream 
DEP+=print_ledger_to_string
DEP+=print_ledger_verbose
DEP+=print_summary_to_filename
DEP+=print_summary_to_stream
DEP+=print_summary_to_string 
DEP+=qcmp
DEP+=remove_rows
DEP+=rename_bank
DEP+=rename_credit 
DEP+=rename_partition 
DEP+=repartition
DEP+=row_delim_char
DEP+=row_delim_str
DEP+=small_norm
DEP+=sort_by_status
DEP+=space 
DEP+=standalone 
DEP+=str_equal 
DEP+=str_strip
DEP+=strip_ledger 
DEP+=swap_rows
DEP+=trim_ledger  
DEP+=unique
DEP+=untotaled 
DEP+=usage
DEP+=which
DEP+=which_bank_total
DEP+=which_credit_total

OBJ=$(foreach name, $(DEP), $(OBJDIR)$(name).o)
TESTOBJ=$(foreach name, $(DEP), $(TESTDIR)$(name)/test_$(name).o)
TESTBIN=$(foreach name, $(DEP), $(TESTDIR)$(name)/test)

all: $(BIN)
	
$(BIN): $(OBJ) 
	$(CC) $(OBJ) -o $(BIN) 

$(OBJDIR)%.o: $(SRCDIR)%.c dirs
	$(CC) $(CCFLAGS) $< -o $@ 

.INTERMEDIATE: dirs

dirs:
	mkdir -p $(OBJDIR)

clean-all: clean clean-tests clean-tutorial

clean:
	rm -rf $(OBJDIR)
	rm -f  $(BIN)

clean-tests:
	rm -f $(TESTOBJ)
	rm -f $(TESTBIN)
	rm -rf $(TESTDIR)main/condensed
	rm -rf $(TESTDIR)main/summaries
	rm -f $(TESTDIR)main/*.txt
	rm -f $(TESTDIR)print_ledger_to_filename/*.txt
	rm -f $(TESTDIR)print_summary_to_filename/*.txt

clean-tutorial:
	rm -f $(TUTORIALDIR)tutorial.aux
	rm -f $(TUTORIALDIR)tutorial.log
	rm -f $(TUTORIALDIR)tutorial.out
	rm -f $(TUTORIALDIR)tutorial.synctex.gz
	rm -f $(TUTORIALDIR)tutorial.toc