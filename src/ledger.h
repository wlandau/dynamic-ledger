#ifndef LEDGER_H
#define LEDGER_H

/**
 * @file        ledger.h
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 * @brief       Main header file.
 * @details     Includes all typedefs and function declarations, 
 *              along with some of the macros.
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"


/**
 * @defgroup Totals_Macros Totals Macros
 * @brief Indices for credit and bank totals.
 * 
 * @details Ledger.bank_totals and Ledger.credit_totals are arrays of doubles
 *          that store various summaries of the ledger: for example, how much
 *          total money has cleared in a particular bank. These macros
 *          store indices that say which entry in Ledger.bank_totals 
 *          and Ledger.credit_totals stores which total. 
 *
 * @{
 */

/** 
 * In Ledger.bank_totals, etc., index of money 
 * not yet arrived. This does not include 
 * pending money.
 */ 
#define I_NOT_THERE_YET   0   

/** 
 * In Ledger.bank_totals, etc., index of the money
 * listed as "pending" on the bank's website. 
 */ 
#define I_PENDING         1   

/**
 * In Ledger.bank_totals, etc., index of "available" 
 * balance. 
 */ 
#define I_CLEARED         2  

/**
 * In Ledger.bank_totals, etc., index of pending 
 * balance (pending money + "available" balance). 
 */
#define I_PENDING_BAL     3    	

/** 
 * In Ledger.bank_totals, etc., index of overall 
 * balance. This is the true balance: "available" 
 * balance + pending money + money not yet arrived. 
 */
#define I_OVERALL_BAL     4   

/** Number of entries in Ledger.bank_totals, etc. */  
#define N_TOTALS          5   

/** @} */


/**
 * @defgroup Return_Value_Macros Return Value Macros
 * @brief Return values from various functions.
 * 
 * @details Some functions have return types of err_t, bool_t, or index_t.
 *          These macros define the values that these types can take on.
 *
 * @{
 */
 
/** 
 * @brief   Success return code.
 * @details Return value indicating a success for functions with return type err_t. 
 */
#define LSUCCESS   0  

/** 
 * @brief   Failure return code.
 * @details Return value indicating a failure for functions with return type err_t. 
 */
#define LFAILURE   1   

/** 
 * @brief   "No" return code.
 * @details Return value indicating a "yes" for functions with return type bool_t. 
 */
#define LNO    0   

/** 
 * @brief   "Yes" return code.
 * @details Return value indicating a "no" for functions with return type bool_t. 
 */
#define LYES   1   

/**
 * For functions returning an index_t type (usually array
 * lookup functions like which), this is the return value 
 * indicating that the index of a candidate entry was not 
 * found in the respective array. 
 */
#define NO_INDEX   -1  

/** @} */

 
/**
 * @defgroup Internal_Macros Internal Macros
 * @brief Internal macros
 * 
 * @details These macros define internal parameters such the maximum size 
 *          of filenames and the number of fields (columns) in a ledger file.
 *
 * @{
 */

/** 
 * @brief Maximum entry size.
 * @details Maximum number of characters for the entries in Ledger.entries.
 */
#define ENTRYSIZE      256         

/** 
 * @brief   "Epsilon"
 * @details A small constant used to check if doubles and floats round to 0.00. 
 */
#define EPS            0.000025   

/**
 * @brief   File name size.
 * @details Maximum number of characters for filenames 
 */
#define FILENAMESIZE   256        

/**
 * @brief   Line size.
 * @details Maximum number of characters for each line in
 *          an input ledger file. 
 */
#define LINESIZE       4096       
                                       
/** 
 * @brief   Number of fields (columns).
 * @details Number of columns in the ledger. Each column
 *          represents a particular feature of a transaction
 *          (row). The fields include transaction amount,
 *          transaction status code, credit account, bank
 *          account, bank partition, and description.
 */
#define NFIELDS        6          

/** 
 * @brief The empty string. 
 */
#define NIL            "\0"       

/** @} */


/**
 * @defgroup Return_Types Return Types
 * @brief Return types
 * 
 * @details Defines the return types of most functions.
 *
 * @{
 */

/** 
 * @brief   Error status type. 
 * @details The error status can take on values LSUCCESS and LFAILURE.
 */
typedef int err_t;   

/** 
 * @brief   Boolean type.
 * @details Can take on values LYES or LNO.
 */
typedef int bool_t;        

/** 
 * @brief   Array index type.
 * @details Index in an array (used for lookup functions). 
 */
typedef int index_t;       

/** 
 * @brief   Color code type.
 * @details Type definition for coloring output to the terminal window. 
 */
typedef char* color_t;   

/** @} */


/**
 * @brief     Stores an individual ledger.
 * @details   Stores the spreadsheet associated with the ledger
 *            along with important summaries. This is the core
 *            data type of the program.
 */

typedef struct {
  char *filename;              /**< Name of the file that the ledger came from. */ 
  char **banks;                /**< Array of names of all the bank accounts 
                                   in the ledger. */ 
  char **credits;              /**< Array of names of all the credit accounts 
                                   in the ledger. */ 
  char ***partitions;          /**< Arrays of names of all the partitions of all 
                                   the bank accounts in the ledger. */ 
  char ***entries;             /**< The matrix of actual entries in the ledger. 
                                   Rows are individual transactions, and columns 
                                   are fields like the amount, status, and bank 
                                   of the transaction.*/
  int nrows;                   /**< Number of rows in the ledger: i.e., 
                                   number of transactions.*/
  int nbanks;                  /**< Number of bank accounts 
                                   (including an automatic unnamed bank account).*/
  int ncredits;                /**< Number of credit accounts 
                                   (including an automatic unnamed credit account).*/
  int *npartitions;            /**< Number of credit accounts 
                                   (including an automatic unnamed partition).*/
  double **bank_totals;        /**< Stores how much money is in each bank account. 
                                   For each bank,
                                   this includes the amount of available money, 
                                   pending money, etc.*/
  double **credit_totals;      /**< Stores how much money is in each credit account. 
                                   For each account,
                                   this includes the amount of available money, 
                                   pending money, etc.*/
  double **partition_totals;   /**< Stores how much money will be in each partition
                                   of each bank account after all charges clear */
} Ledger;


/**
 * @defgroup Utility_Functions Utility Functions
 * @brief Utility functions.
 * 
 * @details These are miscellaneous utility functions.
 *          Many are for checking the quality of the data.
 *
 * @{
 */

/** 
 * @brief  Checks whether a character is a column separator.
 * @param  c Character to check.
 * @return bool_t: LYES or LNO
 */
bool_t col_delim_char(char c);

/** 
 * @brief  Tests if any of the partitions in a given bank have nonzero balance.
 * @param  ledger A pointer to a Ledger object.
 * @param  bank Index of the bank in ledger->banks.
 * @return bool_t: LYES or LNO
 */
bool_t filled_partitions(Ledger *ledger, int bank); 

/** 
 * @brief  Tests if the given input file is usable.
 * @param  filename A character array giving the full path fo the filename.
 * @return bool_t: LYES or LNO
 */   
bool_t input_file(char *filename);

/** 
 * @brief  Checks if a character string can be converted into
           a meaningful floating point number.
 * @param  s A character string that looks like a number to humans.
 * @return bool_t: LYES or LNO
 */  
bool_t legal_double(char *s);  

/** 
 * @brief  Checks if a the AMOUNTS column in the ledger stores strings that
           can be converted into meaningful floating point numbers.
 * @param  ledger A pointer to a Ledger object.
 * @return bool_t: LYES or LNO
 */  
bool_t legal_amounts(Ledger *ledger); 

/** 
 * @brief  Checks if a character string is one of the legal
 *         status codes defined in the Status_Macros module.
 * @param  s A character string representing a status code.
 * @return bool_t: LYES or LNO
 */ 
bool_t legal_status_code(char *s); 

/** 
 * @brief  Checks if all the character strings in the
 *         STATUS column of the ledger are legal
 *         status codes as defined in the Status_Macros module.
 * @param  ledger A pointer to a Ledger object.
 * @return bool_t: LYES or LNO
 */ 
bool_t legal_status_codes(Ledger *ledger);

/** 
 * @brief  Checks if a status code "locks" a transaction.
 * @param  status A character string representing a status code.
 * @return bool_t: LYES or LNO
 */  
bool_t locked(char *status);

/** 
 * @brief  Tests if the given output file is usable.
 * @param  filename A character array giving the full path fo the filename.
 * @return bool_t: LYES or LNO
 */   
bool_t output_file(char *filename); 

/** 
 * @brief  Checks whether a character is a row separator.
 * @param  c Character to check.
 * @return bool_t: LYES or LNO
 */
bool_t row_delim_char(char c);

/** 
 * @brief  Checks whether a floating point number rounds to 0.00.
 * @param  d Double-precision floating point number to check.
 * @return bool_t: LYES or LNO
 */
bool_t small_norm(double d);

/** 
 * @brief  Checks whether a character is a whitespace character.
 * @param  c Character to check
 * @return bool_t: LYES or LNO
 */
bool_t space(char c);

/** 
 * @brief  Checks whether two strings are equal.
 * @param  s1 First string to check.
 * @param  s2 Second string to check.
 * @return bool_t: LYES or LNO
 */
bool_t str_equal(const char *s1, const char *s2);

/** 
 * @brief  Checks if account totals have been calculated for a Ledger object.
 * @param  ledger A pointer to a Ledger object.
 * @return bool_t: LYES or LNO
 */ 
bool_t untotaled(Ledger *ledger);

/** 
 * @brief  Finds the correct color code for an amount in summary output.
 * @param  d A double precision number representing some amount of money.
 * @param  usecolor An int: 1 if color-coded printing is enabled and 0 otherwise.
 * @return color_t: One of the color codes defined in the Printing_Macros
 *                  module.
 */ 
color_t color(double d, int usecolor); 
 
/** 
 * @brief  Finds the first column delimiter in a string.
 * @param  s Character string to check.
 * @return index_t
 */
index_t col_delim_str(char *s);     

/** 
 * @brief  Finds the first row delimiter in a string.
 * @param  s Character string to check.
 * @return index_t
 */                                   
index_t row_delim_str(char *s);

/** 
 * @brief  Finds an occurrence of "find" in "s".
 * @param  s Array of character strings.
 * @param  find Character string to find.
 * @param  n Int: how many elements in s.
 * @return index_t
 */ 
index_t which(char **s,  char *find, int n);

/** 
 * @brief  Given a status code, finds the correct index in 
 *         the bank_totals array member of the Ledger type.
 * @param  status Character string status code.
 * @return index_t
 */ 
index_t which_bank_total(char *status);

/** 
 * @brief  Given a status code, finds the correct index in 
 *         the credit_totals array member of the Ledger type.
 * @param  status Character string status code.
 * @return index_t
 */ 
index_t which_credit_total(char *status);

/** 
 * @brief  Comparison function for character strings in qsort.
 * @param  a First character string.
 * @param  b Second character string. 
 * @return index_t
 */ 
int qcmp(const void *a, const void *b);

/** 
 * @brief  Strips leading and trailing whitespace from a character string.
 * @param  s Character string
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t str_strip(char *s);

/** 
 * @brief  Finds all the unique elements in an array of character strings.
 * @param  a Array of character strings.
 * @param  n Number of elements of s.
 * @param  ret Array of the unique elements of s.
 * @param  nunique Number elements of ret.
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t unique(char **a, int n, char ***ret, int *nunique);

/**
 * @brief  Prints usage details
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t usage();

/** @} */


/**
 * @defgroup Ledger_Memory_Functions Ledger Memory Functions
 * @brief Ledger memory functions
 * 
 * @details These are functions for creating, initializing, copying,
 *          and destroying Ledger objects.
 *
 * @{
 */

/**
 * @brief  Allocates the "entries" member of a Ledger object.
 * @param  ledger pointer to a Ledger object
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t alloc_entries(Ledger* ledger);

/**
 * @brief  Allocates space for the numerical summaries of the ledger.
 * @param  ledger pointer to a Ledger object
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t alloc_totals(Ledger* ledger);

/**
 * @brief  Frees the "entries" member of a Ledger object.
 * @param  ledger pointer to a Ledger object
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t free_entries(Ledger* ledger); 

/**
 * @brief  Frees the account names and numerical summaries of a Ledger object.
 * @param  ledger pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t free_for_retotal(Ledger* ledger);

/**
 * @brief  Frees a whole Ledger object.
 * @param  ledger pointer to a pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t free_ledger(Ledger** ledger); 

/**
 * @brief  Gets the account names of a Ledger object.
 * @param  ledger pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t get_names(Ledger *ledger);

/**
 * @brief  Computes numerical summaries of a Ledger object.
 * @param  ledger pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t get_totals(Ledger *ledger);

/**
 * @brief  Creates a new Ledger object
 * @param  ledger pointer to a pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t new_ledger(Ledger **ledger); 

/**
 * @brief  Copies one Ledger object into another.
 * @param  out_ledger pointer to a pointer to the output Ledger object.
 * @param  in_ledger pointer to the input Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t copy_ledger(Ledger **out_ledger, Ledger *in_ledger);

/** @} */


/**
 * @defgroup Ledger_Modify_Functions Ledger Modify Functions
 * @brief Functions for modifying Ledger objects.
 * 
 * @details These are functions for modifying Ledger objects.
 *          These include (but are not limited to) functions
 *          to edit entries and rows, copy and paste rows,
 *          and trim and condense entire Ledger objects.
 *
 * @{
 */

/**
 * @brief  Cleans a ledger object
 * @param  ledger Pointer to a Ledger object.
 * @param  sort_locked Set to 1 to bring all locked rows to the top.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t clean(Ledger *ledger, int sort_locked);

/**
 * @brief  Condenses a ledger object
 * @param  ledger Pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t condense(Ledger *ledger);

/**
 * @brief  Copies selected rows (transactions).
 * @param  ledger Pointer to a Ledger object.
 * @param  clipboard Pointer to a pointer to the Ledger object to copy the rows into.
 * @param  rows The indices of the rows in ledger to be copied.
 * @param  howmany Number of elements of rows.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t copy_rows(Ledger *ledger, Ledger **clipboard, int *rows, int howmany);

/**
 * @brief  Cut selected rows (transactions).
 * @param  ledger Pointer to a Ledger object.
 * @param  clipboard Pointer to a pointer to the Ledger object to copy the rows into.
 * @param  rows The indices of the rows in ledger to be cut.
 * @param  howmany Number of elements of rows.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t cut_rows(Ledger *ledger, Ledger **clipboard, int *rows, int howmany);

/**
 * @brief  Modify a ledger entry and update the Ledger object accordingly.
 * @param  ledger Pointer to a Ledger object.
 * @param  entry New entry (character string).
 * @param  row The row of the entry to overwrite.
 * @param  field The field (column) of the entry to overwrite.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t edit_entry(Ledger *ledger, char *entry, int row, int field);

/**
 * @brief  Modify a ledger entry and DO NOT update the Ledger object accordingly.
 * @param  ledger Pointer to a Ledger object.
 * @param  entry New entry (character string).
 * @param  row The row of the entry to overwrite.
 * @param  field The field (column) of the entry to overwrite.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t edit_entry_noretotal(Ledger *ledger, char *entry, int row, int field);


/**
 * @brief  Modify a whole row (transaction) and update the Ledger object accordingly.
 * @param  ledger Pointer to a Ledger object.
 * @param  entries New row (array of character string entries).
 * @param  row The row to overwrite.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t edit_row(Ledger *ledger, char **entries, int row);

/**
 * @brief  Map a character string to part of a column.
 * @param  ledger Pointer to a Ledger object.
 * @param  entry Character string to map.
 * @param  rows The rows to map to.
 * @param  nrows Number of elements of rows.
 * @param  field Column to map to.
 * @param  append Append option.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t map_to_column(Ledger *ledger, char *entry, int *rows, 
                    int nrows, int field, int append);


/**
 * @brief  Map a character string a region of the spreadsheet.
 * @param  ledger Pointer to a Ledger object.
 * @param  entry Character string to map.
 * @param  rows Rows of entries to map to.
 * @param  nrows Number of elements of rows.
 * @param  fields Columns of entries to map to.
 * @param  nfields Number of elements of fields.
 * @param  append Append option.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t map_to_grid(Ledger *ledger, char *entry, int *rows, int nrows,
                  int *fields, int nfields, int append);

/**
 * @brief  Map a character string multiple entries.
 * @param  ledger Pointer to a Ledger object.
 * @param  entry Character string to map.
 * @param  rows Rows of entries to map to.
 * @param  fields Columns of entries to map to.
 * @param  howmany Number of elements of rows and fields.
 * @param  append Append option.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t map_to_multiple(Ledger *ledger, char *entry, int *rows, 
                    int *fields, int howmany, int append);

/**
 * @brief  Insert blank rows.
 * @param  ledger Pointer to a Ledger object.
 * @param  row Where to insert the rows.
 * @param  howmany How many blank rows to insert.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t insert_rows(Ledger *ledger, int row, int howmany); 

/**
 * @brief  Move rows to a specified location.
 * @param  ledger Pointer to a Ledger object.
 * @param  rows Array of the indices of the rows to move.
 * @param  nrows Number of rows to move.
 * @param  moveto Where to move the rows: i.e., the destination row index.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t move_rows(Ledger *ledger, int *rows, int nrows, int moveto);

/**
 * @brief  Paste rows into a specified location
 * @param  ledger Pointer to a Ledger object.
 * @param  clipboard Pointer to a Ledger object containing the rows to paste.
 * @param  where Where to paste the rows: i.e., the destination row index.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t paste_rows(Ledger *ledger, Ledger *clipboard, int where);

/**
 * @brief  Permute rows (transactions).
 * @param  ledger Pointer to a Ledger object.
 * @param  order Array of indices to sort the rows by.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t permute_rows(Ledger *ledger, int *order);

/**
 * @brief  Safely renames a bank account.
 * @param  ledger Pointer to a Ledger object.
 * @param  from Which bank account to rename.
 * @param  to New name for the bank account.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t rename_bank(Ledger *ledger, char *from, char *to);

/**
 * @brief  Safely renames a credit account.
 * @param  ledger Pointer to a Ledger object.
 * @param  from Which credit account to rename.
 * @param  to New name for the credit account.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t rename_credit(Ledger *ledger, char *from, char *to);

/**
 * @brief  Safely renames a partition bank account.
 * @param  ledger Pointer to a Ledger object.
 * @param  bank Bank account of the partition to rename.
 * @param  from Which partition to rename.
 * @param  to New name for the partition.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t rename_partition(Ledger *ledger, char *bank, char *from, char *to);

/**
 * @brief  Removes rows (transactions) marked for removal.
 * @param  ledger Pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t remove_rows(Ledger *ledger);

/**
 * @brief  Recalculate names and totals.
 * @param  ledger Pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t retotal(Ledger *ledger);

/**
 * @brief  Removes blank rows.
 * @param  ledger Pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t trim_ledger(Ledger *ledger);

/**
 * @brief  Sorts rows (transactions) by transaction status code.
 * @param  ledger Pointer to a Ledger object.
 * @param  sort_locked Set to 1 to send all locked transactions to the top and 0 otherwise.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t sort_by_status(Ledger *ledger, int sort_locked);

/**
 * @brief  Removes whitespace from the entries of a Ledger object
 * @param  ledger Pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t strip_ledger(Ledger *ledger);     

/**
 * @brief  Interchanges two rows of a ledger object.
 * @param  ledger Pointer to a Ledger object.
 * @param  row1 Index of the first row.
 * @param  row2 Index of the second row.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t swap_rows(Ledger *ledger, int row1, int row2);

/**
 * @brief  Repartitions a bank account.
 * @param  ledger Pointer to a Ledger object.
 * @param  bank Bank account to repartition.
 * @param  partitions Array of character strings giving the names of the new partitions.
 * @param  amounts_arg Amount allocated to each partition
 * @param  npartitions Number of character strings in "partitions"
 * @param  as_percentages Whether to interpret the entries in amounts_arg as percentages.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t repartition(Ledger *ledger, char *bank, char **partitions, 
                  double *amounts_arg, int npartitions, int as_percentages);
                  
/**
 * @brief  Unlock all cleared transactions.
 * @param  ledger Pointer to a Ledger object.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t unlock(Ledger *ledger);

/** @} */


/**
 * @defgroup Ledger_Input_Functions Ledger Input Functions
 * @brief Functions for reading Ledger objects.
 * 
 * @details These are functions for reading Ledger objects from
 *          files, file streams, and character strings.
 *
 * @{
 */


/**
 * @brief  Parse a character while reading a ledger from a file.
 * @param  ledger Pointer to a Ledger object.
 * @param  c The character to parse.
 * @param  char_index The index of the character in the current ledger entry.
 * @param  field The field (column) of the current ledger entry being read.
 * @param  row The row (transaction) of the current ledger entry being read.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t parse_char(Ledger *ledger, char c, int *char_index, int *field, int *row);

/**
 * @brief  Get ledger entries from a file.
 * @param  ledger Pointer to a Ledger object.
 * @param  filename Full path of the file to read from.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t get_entries_from_filename(Ledger *ledger, char *filename); 

/**
 * @brief  Get ledger entries from a file stream.
 * @param  ledger Pointer to a Ledger object.
 * @param  fp FILE pointer to the file stream to read from.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t get_entries_from_stream(Ledger *ledger, FILE *fp);

/**
 * @brief  Get ledger entries from a string.
 * @param  ledger Pointer to a Ledger object.
 * @param  s Character string to read from.
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t get_entries_from_string(Ledger *ledger, char *s);  

/**
 * @brief  Recommended way to read in a Ledger object.
 * @param  ledger Pointer to a Ledger object.
 * @param  filename Full path of the file to read from.
 * @param  fp FILE pointer to the file stream to read from.
 * @param  str Character string to read from.
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t get_ledger(Ledger **ledger, char* filename, FILE *fp, char *str);

/** @} */


/**
 * @defgroup Ledger_Output_Functions Ledger Output Functions
 * @brief Functions to output Ledger objects.
 * 
 * @details These are functions to output Ledger objects to
 *          files, file streams, and character strings.
 *
 * @{
 */

/**
 * @brief  Print ledger entries to a file.
 * @param  ledger Pointer to a Ledger object.
 * @param  filename Full path of the file to print to.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t print_ledger_to_filename(Ledger *ledger,  char *filename);

/**
 * @brief  Print ledger entries to a file stream.
 * @param  ledger Pointer to a Ledger object.
 * @param  fp FILE pointer to the file stream to print to.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t print_ledger_to_stream(Ledger *ledger, FILE *fp);

/**
 * @brief  Print ledger entries to a string.
 * @param  ledger Pointer to a Ledger object.
 * @param  s Character string to write to.
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t print_ledger_to_string(Ledger *ledger, char **s);

/**
 * @brief  Print out all the information on a Ledger object to a file stream.
 * @param  ledger Pointer to a Ledger object.
 * @param  fp FILE pointer to the file stream to print to.
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t print_ledger_verbose(Ledger *ledger, FILE *fp);

/** @} */


/**
 * @defgroup Ledger_Summary_Functions Ledger Summary Functions
 * @brief Functions to summarize Ledger objects.
 * 
 * @details These are functions to output \e summaries of Ledger objects to
 *          files, file streams, and character strings.
 *
 * @{
 */

/**
 * @brief  Print out a summary of a Ledger object to a file
 * @param  ledger Pointer to a Ledger object.
 * @param  filename Full path of the file to print to.
 * @param  usecolor Include command line interface color codes?
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t print_summary_to_filename(Ledger *ledger,  char *filename, int usecolor);

/**
 * @brief  Print out a summary of a Ledger object to a file
 * @param  ledger Pointer to a Ledger object.
 * @param  fp FILE pointer of file stream to print to.
 * @param  usecolor Include command line interface color codes?
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t print_summary_to_stream(Ledger *ledger, FILE *fp, int usecolor);                     

/**
 * @brief  Print out a summary of a Ledger object to a file
 * @param  ledger Pointer to a Ledger object.
 * @param  s Character string to print to.
 * @param  usecolor Include command line interface color codes?
 * @return err_t: LSUCCESS or LFAILURE
 */ 
err_t print_summary_to_string(Ledger *ledger, char **s, int usecolor);

/** @} */


/**
 * @defgroup Top_Level_Functions Top Level Functions
 * @brief Top level functions.
 * 
 * @details These are functions that govern the program at the top leve.
 *          For example, standalone() is the main function of the command
 *          line interface version of the program.
 *
 * @{
 */

/**
 * @brief  Top level function of the standalone command line interface version
 * @param  argc Number of arguments to int main.
 * @param  argv Arguments to int main.
 * @return err_t: LSUCCESS or LFAILURE
 */
err_t standalone(int argc, char **argv);

/** @} */

#endif
