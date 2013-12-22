## Dynamic Ledger: a minimalist personal accounting software package

## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

## Define an executable target "dl", which will be installed into the
## directory named by the predefined variable $(bindir).
bin_PROGRAMS = dl

## things to keep in the tarball
dist_data_DATA = doc/source.pdf man/dl.1 tutorial/tutorial.pdf tutorial/ledger.txt

## Define the list of source files for the "dl" target.
dl_SOURCES=src/ledger.h
dl_SOURCES+=src/user_settings.h
dl_SOURCES+=src/main.c
dl_SOURCES+=src/alloc_entries.c
dl_SOURCES+=src/alloc_totals.c
dl_SOURCES+=src/clean.c
dl_SOURCES+=src/col_delim_char.c
dl_SOURCES+=src/col_delim_str.c
dl_SOURCES+=src/color.c
dl_SOURCES+=src/condense.c 
dl_SOURCES+=src/copy_ledger.c
dl_SOURCES+=src/copy_rows.c
dl_SOURCES+=src/cut_rows.c
dl_SOURCES+=src/edit_entry.c
dl_SOURCES+=src/edit_entry_noretotal.c
dl_SOURCES+=src/edit_row.c
dl_SOURCES+=src/filled_partitions.c
dl_SOURCES+=src/free_entries.c
dl_SOURCES+=src/free_for_retotal.c 
dl_SOURCES+=src/free_ledger.c
dl_SOURCES+=src/get_entries_from_filename.c
dl_SOURCES+=src/get_entries_from_stream.c
dl_SOURCES+=src/get_entries_from_string.c 
dl_SOURCES+=src/get_ledger.c
dl_SOURCES+=src/get_names.c 
dl_SOURCES+=src/get_totals.c 
dl_SOURCES+=src/input_file.c 
dl_SOURCES+=src/insert_rows.c
dl_SOURCES+=src/legal_amounts.c 
dl_SOURCES+=src/legal_double.c
dl_SOURCES+=src/legal_status_code.c
dl_SOURCES+=src/legal_status_codes.c
dl_SOURCES+=src/locked.c
dl_SOURCES+=src/map_to_column.c
dl_SOURCES+=src/map_to_multiple.c
dl_SOURCES+=src/move_rows.c
dl_SOURCES+=src/new_ledger.c
dl_SOURCES+=src/output_file.c
dl_SOURCES+=src/parse_char.c
dl_SOURCES+=src/paste_rows.c
dl_SOURCES+=src/permute_rows.c
dl_SOURCES+=src/print_ledger_to_filename.c
dl_SOURCES+=src/print_ledger_to_stream.c
dl_SOURCES+=src/print_ledger_to_string.c
dl_SOURCES+=src/print_ledger_verbose.c
dl_SOURCES+=src/print_summary_to_filename.c
dl_SOURCES+=src/print_summary_to_stream.c
dl_SOURCES+=src/print_summary_to_string.c 
dl_SOURCES+=src/qcmp.c
dl_SOURCES+=src/remove_rows.c
dl_SOURCES+=src/rename_bank.c
dl_SOURCES+=src/rename_credit.c 
dl_SOURCES+=src/rename_partition.c 
dl_SOURCES+=src/repartition.c
dl_SOURCES+=src/retotal.c
dl_SOURCES+=src/row_delim_char.c
dl_SOURCES+=src/row_delim_str.c
dl_SOURCES+=src/small_norm.c
dl_SOURCES+=src/sort_by_status.c
dl_SOURCES+=src/space.c
dl_SOURCES+=src/standalone.c 
dl_SOURCES+=src/str_equal.c 
dl_SOURCES+=src/str_strip.c
dl_SOURCES+=src/strip_ledger.c 
dl_SOURCES+=src/swap_rows.c
dl_SOURCES+=src/trim_ledger.c  
dl_SOURCES+=src/unique.c
dl_SOURCES+=src/unlock.c
dl_SOURCES+=src/untotaled.c 
dl_SOURCES+=src/usage.c
dl_SOURCES+=src/which.c
dl_SOURCES+=src/which_bank_total.c
dl_SOURCES+=src/which_credit_total.c

## Define an independent executable script for inclusion in the distribution
## archive. It will not be installed on an end user's system, however.
dist_noinst_SCRIPTS = autogen.sh

## Where to put the man page
man1_MANS=man/dl.1
