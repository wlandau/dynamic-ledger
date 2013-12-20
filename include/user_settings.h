#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

/**
 * @file        user_settings.h
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License >= 3.0 (See COPYING.txt)
 * @brief       Header file for user settings.
 * 
 * @details     Users can redefine the macros in this file to set program preferences 
 *              at compile time.
 */

/**
 * @defgroup Columns
 * @brief Ordering of the columns in the ledger file.
 * 
 * @details These numbers define the ordering of the columns
 *          Each macro stores a column index. For example, 
 *          if BANK is 3, then the ledger file should have
 *          bank account names in column 3. All column indices
 *          must be from 0 to 5 inclusive.
 *
 * @{
 */
 
/** 
 * @brief   Amount index.
 * @details Column index for transaction amounts in the ledger file.  
 */
#define AMOUNT        0  

/** 
 * @brief   Status index.
 * @details Column index for transaction status codes in the ledger file. 
 */
#define STATUS        1   

/** 
 * @brief   Credit index.
 * @details Column index for credit account names in the ledger file. 
 */
#define CREDIT        2   

/** 
 * @brief   Bank index. 
 * @details Column index for bank account names in the ledger file. 
 */
#define BANK          3  
 
/** 
 * @brief   Partition index.
 * @details Column index for bank partition names in the ledger file. 
 */
#define PARTITION     4   

/** 
 * @brief   Description index.
 * @details Column index for transaction descriptions in the ledger file. 
 */
#define DESCRIPTION   5   

/** @} */


/**
 * @defgroup Separator_Macros
 * @brief Row and column separators
 * 
 * @details These macros define which characters are used to separate
 *          rows and columns of the ledger file. For example, if
 *          COLUMN_SEPARATORS is "," then the program will expect
 *          the ledger file to be stored in Comma Separated Values 
 *          (CSV) format. The row separators should be different from
 *          the column separators.
 *
 * @{
 */


/** 
 * @brief   Row separators.
 * @details Characters that encode the end of a row in the ledger file 
 */
#define ROW_SEPARATORS      "\n\r" 

/** 
 * @brief Column separators.
 * @details Characters that encode the end of a column in the ledger file 
 */
#define COLUMN_SEPARATORS   "\t"   

/** @{ */


/**
 * @defgroup Status_Macros
 * @brief Transaction status codes.
 * 
 * @details Transaction status codes tell the program where each transaction
 *          is in time: i.e., whether it's pending in the bank or
 *          it has not shown up in the credit account, etc. These macros are
 *          the character strings that the user manually enters in the STATUS
 *          column of the ledger file for each transaction.
 *
 * @{
 */

/** 
 * @brief   Made with a credit account, but not arrived online.
 * @details Use this status if you make a transaction with a 
 *          credit account and the transaction hasn't shown up
 *          yet on the credit account's website. 
 */
#define CREDIT_NOT_THERE_YET   "cn"      

/** 
 * @brief   Pending in a credit account.
 * @details Transactions that show up as "pending" 
 *          on credit accounts 
 */
#define CREDIT_PENDING         "cp"    

/** 
 * @brief   Charged to a credit account.
 * @details Transactions that show up as "cleared" 
 *          in a credit account, but for which no 
 *          payment from a bank has been made. 
 */  
#define CREDIT_CHARGED         "c" 

/** 
 * @brief   Not yet arrived at the bank.
 * @details The transaction has cleared the credit account
 *          (if applicable), but the transaction
 *          or associated credit card payment hasn't shown up 
 *          yet on the bank account's website. 
 */
#define NOT_THERE_YET          "n" 

/** 
 * @brief   Pending in a bank.
 * @details Transactions that show up as "pending" 
 *          in bank accounts.
 */
#define PENDING                "p" 

/** 
 * @brief   Locked status.
 * @details Cleared, but protected: that is, if a transaction is
 *          locked and has a nonzero amount, then the trim_ledger,
 *          condense, and clean functions will not remove it. 
 */
#define LOCKED                 "l"      

/** 
 * @brief   Pending removal from the ledger.
 * @details About to be removed from the ledger by remove_rows.
 */
#define REMOVE                 "REMOVE"  

/** @{ */


/**
 * @defgroup Printing_Macros
 * @brief Print formatting macros.
 * 
 * @details These macros define settings for printing summaries of ledgers.
 *
 * @{
 */

/** 
 * @brief   Option to print empty accounts in summaries.
 * @details Set to 1 to include empty named accounts in summaries. 
 *          Set to 0 to ignore accounts with balances of $0.00.
 */
#define PRINT_EMPTY_ACCOUNTS 0  

/** 
 * @brief   Option to use color-coded printing in summaries.
 * @details Set to 1 to enable color-coded printing to the terminal 
 *          in summaries. Set to 0 for no coloring.
 */
#define USE_COLOR   1  

/** 
 * @brief   Normal text color code.
 * @details Terminal color code for regular text. 
 */
#define NORMAL_COLOR     "\x1B[0m"    

/** 
 * @brief   Negative text color code. 
 * @details Terminal color code for negative totals. 
 */
#define NEGATIVE_COLOR   "\x1B[31m"   

/** 
 * @brief   Positive text color code. 
 * @details Terminal color code for positive totals. 
 */
#define POSITIVE_COLOR   "\x1B[32m"   

/** 
 * @brief   Zero text color code. 
 * @details Terminal color code for empty totals. 
 */
#define ZERO_COLOR       "\x1B[34m"   

/** @{ */

#endif
