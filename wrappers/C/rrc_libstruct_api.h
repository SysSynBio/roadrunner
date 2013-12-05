/**
 * @file rrc_libstruct_api.h
 * @brief roadRunner C API 2012
 * @author Totte Karlsson & Herbert M Sauro
 *
 * <--------------------------------------------------------------
 * This file is part of cRoadRunner.
 * See http://code.google.com/p/roadrunnerlib for more details.
 *
 * Copyright (C) 2012-2013
 *   University of Washington, Seattle, WA, USA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * In plain english this means:
 *
 * You CAN freely download and use this software, in whole or in part, for personal,
 * company internal, or commercial purposes;
 *
 * You CAN use the software in packages or distributions that you create.
 *
 * You SHOULD include a copy of the license in any redistribution you may make;
 *
 * You are NOT required include the source of software, or of any modifications you may
 * have made to it, in any redistribution you may assemble that includes it.
 *
 * YOU CANNOT:
 *
 * redistribute any piece of this software without proper attribution;
*/
#ifndef rrc_libstruct_apiH
#define rrc_libstruct_apiH
#include "rrc_exporter.h"
#include "rrc_types.h"
//---------------------------------------------------------------------------
#if defined(__cplusplus)
namespace rrc
{
extern "C"
{
#endif

/*! \brief Returns the L0 Matrix.

L0 is defined such that  L0 Nr = N0. L0 forms part of the link matrix, L.  N0 is the set of
linear dependent rows from the lower portion of the reordered stoichiometry matrix.

\param[in] handle Handle to a RoadRunner instance
\return Returns null if it fails, otherwise returns the L0 matrix.

\remarks To free the returned matrix call freeMatrix with the matrix
as parameter.
\ingroup Stoich
*/
C_DECL_SPEC RRDoubleMatrixPtr rrcCallConv getL0Matrix(RRHandle handle);

/*! \brief Calculates the eigen-vectors of a square real matrix.
This function calculates the complex (right)eigenvectors of the given real matrix. The complex matrix
returned contains the eigenvectors in the columns, in the same order as LibLA_getEigenValues.

The right eigenvector v(j) of A satisfies:
\par
A * v(j) = lambda(j) * v(j)
\param[in] matrix Handle to a RRMatrix
\return Returns null if it fails, otherwise returns a RRComplexMatrix.
\ingroup Stoich
*/
C_DECL_SPEC RRComplexMatrixPtr rrcCallConv getEigenVectors(RRDoubleMatrixPtr matrix);


/*! \brief Calculates the eigen-vectors of a square nonsymmetrix complex matrix.
This function calculates the complex (right)eigenvectors of the given real matrix. The complex matrix
returned contains the eigenvectors in the columns, in the same order as getZEigenValues.
The right eigenvector v(j) of A satisfies:
\par
A * v(j) = lambda(j) * v(j)
\param[in] matrix Handle to a RRComplexMatrix
\return Returns null if it fails, otherwise returns a RRComplexMatrix.
\ingroup Stoich
*/
C_DECL_SPEC RRComplexMatrixPtr rrcCallConv getZEigenVectors(RRComplexMatrixPtr matrix);


/*! \brief Returns values for conservation laws using the current initial conditions
\remarks free vector using freeVector function

\return The return value will be zero (0) when successful, and negative (-1) in case
no stoichiometry matrix was loaded beforehand or none of the analysis methods has
been called yet.
\param[in] handle Handle to a RoadRunner instance
\return Returns null if it fails, otherwise returns a RRVectorHandle.
\ingroup Stoich

*/
// int LibStructural_getConservedSums(double* *outArray, int *outLength);
RRVectorPtr getConservedSums(RRHandle handle);


// --------------------------------------------------------------------------------
// General purpose linear algebra methods
// --------------------------------------------------------------------------------

/*!
 \brief Compute the eigenvalues of a double matrix
 \param[in] mat Pointer to a to double matrix 
 \return Returns NULL if it fails, otherwise returns a matrix of eigenvalues.
 The first column will contain the real values and the second column the imaginary values
 \ingroup LinearAlgebra
*/
C_DECL_SPEC RRDoubleMatrixPtr rrcCallConv getEigenvaluesMatrix(const RRDoubleMatrixPtr mat);

/*!
 \brief Compute the eigenvalues of a double matrix

 \param[in] mat Handle to input matrix
 \return Returns null if it fails, otherwise returns a complex vector of eigenvalues.
 \ingroup LinearAlgebra
*/
C_DECL_SPEC RRComplexVectorPtr rrcCallConv getEigenvaluesVector(const RRDoubleMatrixPtr mat);

//---------------------------------------------------------------------------
#if defined(__cplusplus)
}
}
#endif //rrc namespace and extern "C" scopes


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/* Part of ORIGINAL libstruct C wrappers below.. uncomment and cleanup to use with roadrunner, and move above this line */
//---------------------------------------------------------------------------

///*! \brief Load a new stoichiometry matrix.
//
//Loads the stoichiometry matrix into the library. To analyze the stoichiometry
//call one of the following:
//
//\li ::LibStructural_analyzeWithQR,
//\li ::LibStructural_analyzeWithLU,
//\li ::LibStructural_analyzeWithLUandRunTests,
//\li ::LibStructural_analyzeWithFullyPivotedLU or
//\li ::LibStructural_analyzeWithFullyPivotedLUwithTests
//
//
//\remarks if matrix labels are needed it is recommended to call
//::LibStructural_loadSpecies and ::LibStructural_loadReactionNames after
//a call to this function.
//
//\param oMatrix a pointer to a double** matrix
//\param nRows the number of rows of the matrix
//\param nCols the number of columns of the matrix
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred
//*/
//  int LibStructural_loadStoichiometryMatrix (const double ** oMatrix, const int nRows, const int nCols);
//*/
//
//
///*! \brief Load species names and initial values.
//
//This function should be used whenever labeled matrices are important as these
//labels will be used in labeling the structural matrices. This function sets the species
//names (ids). It is also possible to provide an initial condition for each of
//the species. This will be used when calculating the conserved sums.
//
//\param speciesNames an array of strings of species names with length nLength
//\param speciesValues an array of real numbers of species concentrations corresponding
//to the speciesName with the same index
//\param nLength number of elements in speciesNames and speciesValues
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred
//
//\remarks This method should only be called after ::LibStructural_loadStoichiometryMatrix
//
//*/
//  int LibStructural_loadSpecies ( const char** speciesNames, const double* speciesValues, const int nLength);
//
///*! \brief Load reaction names.
//
//This function should be used whenever labeled matrices are important as these
//labels will be used in labeling the structural matrices. This function sets the reaction
//names (ids).
//
//\param reactionNames an array of strings of reaction names with length nLength
//\param nLength number of elements in reactionNames
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred
//
//\remarks This method should only be called after ::LibStructural_loadStoichiometryMatrix
//
//*/
//
//  int LibStructural_loadReactionNames ( const char** reactionNames, const int nLength);
//
///*! \brief Uses QR factorization for structural analysis
//
//This method performs the actual analysis of the stoichiometry matrix (loaded either
//via ::LibStructural_loadStoichiometryMatrix or ::LibStructural_loadSBML. Only after
//one of the analysis methods below has been called are the structural matrices (L0, K0...)
//available.
//
//\li ::LibStructural_analyzeWithQR,
//\li ::LibStructural_analyzeWithLU,
//\li ::LibStructural_analyzeWithLUandRunTests,
//\li ::LibStructural_analyzeWithFullyPivotedLU or
//\li ::LibStructural_analyzeWithFullyPivotedLUwithTests
//
//
//\remarks This is the prefered method for structural analysis.
//
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand see ::LibStructural_loadStoichiometryMatrix
//or ::LibStructural_loadSBML or ::LibStructural_loadSBMLFromFile
//
//*/
//  int LibStructural_analyzeWithQR(char* *outMessage, int *nLength);
///*! \brief Uses LU Decomposition for structural analysis
//
//This method performs the actual analysis of the stoichiometry matrix (loaded either
//via ::LibStructural_loadStoichiometryMatrix or ::LibStructural_loadSBML. Only after
//one of the analysis methods below has been called are the structural matrices (L0, K0...)
//available.
//
//\li ::LibStructural_analyzeWithQR,
//\li ::LibStructural_analyzeWithLU,
//\li ::LibStructural_analyzeWithLUandRunTests,
//\li ::LibStructural_analyzeWithFullyPivotedLU or
//\li ::LibStructural_analyzeWithFullyPivotedLUwithTests
//
//
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand see ::LibStructural_loadStoichiometryMatrix
//or ::LibStructural_loadSBML or ::LibStructural_loadSBMLFromFile
//*/
//  int LibStructural_analyzeWithLU(char* *outMessage, int *nLength);
///*! \brief Uses LU Decomposition for structural analysis
//
//This method performs the actual analysis of the stoichiometry matrix (loaded either
//via ::LibStructural_loadStoichiometryMatrix or ::LibStructural_loadSBML. Only after
//one of the analysis methods below has been called are the structural matrices (L0, K0...)
//available.
//
//\li ::LibStructural_analyzeWithQR,
//\li ::LibStructural_analyzeWithLU,
//\li ::LibStructural_analyzeWithLUandRunTests,
//\li ::LibStructural_analyzeWithFullyPivotedLU or
//\li ::LibStructural_analyzeWithFullyPivotedLUwithTests
//
//
//This method additionally performs the integrated test suite and returns    those results.
//
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand see ::LibStructural_loadStoichiometryMatrix
//or ::LibStructural_loadSBML or ::LibStructural_loadSBMLFromFile
//
//*/
//  int LibStructural_analyzeWithLUandRunTests(char* *outMessage, int *nLength);
///*! \brief Uses fully pivoted LU decomposition for structural analysis.
//
//This method performs the actual analysis of the stoichiometry matrix (loaded either
//via ::LibStructural_loadStoichiometryMatrix or ::LibStructural_loadSBML. Only after
//one of the analysis methods below has been called are the structural matrices (L0, K0...)
//available.
//
//\li ::LibStructural_analyzeWithQR,
//\li ::LibStructural_analyzeWithLU,
//\li ::LibStructural_analyzeWithLUandRunTests,
//\li ::LibStructural_analyzeWithFullyPivotedLU or
//\li ::LibStructural_analyzeWithFullyPivotedLUwithTests
//
//\remarks Unlike the other methods, this method handles only square stoichiometry
//matrices. This method was only included for backward compatibility use
//::LibStructural_analyzeWithQR
//
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand. See ::LibStructural_loadStoichiometryMatrix
//or ::LibStructural_loadSBML or ::LibStructural_loadSBMLFromFile
//*/
//  int LibStructural_analyzeWithFullyPivotedLU(char* *outMessage, int *nLength);
///*! \brief Uses fully pivoted LU decomposition for structural analysis
//
//This method performs the actual analysis of the stoichiometry matrix (loaded either
//via ::LibStructural_loadStoichiometryMatrix or ::LibStructural_loadSBML. Only after
//one of the analysis methods below has been called are the structural matrices (L0, K0...)
//available.
//
//\li ::LibStructural_analyzeWithQR,
//\li ::LibStructural_analyzeWithLU,
//\li ::LibStructural_analyzeWithLUandRunTests,
//\li ::LibStructural_analyzeWithFullyPivotedLU or
//\li ::LibStructural_analyzeWithFullyPivotedLUwithTests
//
//
//This method additionally performs the integrated test suite and returns those results.
//
//\remarks Unlike the other methods, this method handles only square stoichiometry
//matrices. For non-square matrices use a method like ::LibStructural_analyzeWithQR.
//
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand see ::LibStructural_loadStoichiometryMatrix
//or ::LibStructural_loadSBML or ::LibStructural_loadSBMLFromFile
//*/
//  int LibStructural_analyzeWithFullyPivotedLUwithTests(char* *outMessage, int *nLength);

///*! \brief Returns the L0 Matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getL0MatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                char** *outColLabels, int *outColCount);
//
///*! \brief Returns the Nr Matrix.
//The rows of the Nr matrix will be linearly independent.
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getNrMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the Nr Matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getNrMatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                char** *outColLabels, int *outColCount);
//
///*! \brief Returns the Nr Matrix repartitioned into NIC (independent columns) and NDC (dependent columns).
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getColumnReorderedNrMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the Nr Matrix row and column labels (repartitioned into NIC and NDC).
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getColumnReorderedNrMatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                               char** *outColLabels, int *outColCount);
//
///*! \brief Returns the NIC Matrix (the set of linearly independent columns of Nr)
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getNICMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the NIC Matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getNICMatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                 char** *outColLabels, int *outColCount);
///*! \brief Returns the NDC Matrix (the set of linearly dependent columns of Nr).
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getNDCMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the NDC Matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getNDCMatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                 char** *outColLabels, int *outColCount);
///*! \brief Returns the N0 Matrix.
//
//The N0 matrix is the set of linearly dependent rows of N where L0 Nr = N0.
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getN0Matrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the N0 Matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getN0MatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                char** *outColLabels, int *outColCount);
//
///*! \brief Returns L, the Link Matrix, left nullspace (aka nullspace of the transpose Nr).
//
//L will have the structure, [I L0]', such that L Nr  = N
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getLinkMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the row and column labels for the Link Matrix, L
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getLinkMatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                  char** *outColLabels, int *outColCount);
//
///*! \brief Returns the K0 Matrix.
//
//K0 is defined such that K0 = -(NIC)^-1 NDC, or equivalently, [NDC NIC][I K0]' = 0 where [NDC NIC] = Nr
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getK0Matrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the K0 Matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getK0MatrixLabels(char** *outRowLabels, int *outRowCount,
//                                                char** *outColLabels, int *outColCount);
///*! \brief Returns the K matrix (right nullspace of Nr)
//The K matrix has the structure, [I K0]'
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getKMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the K matrix row and column labels.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getKMatrixLabels(char** *outRowLabels, int *outRowCount,
//                                               char** *outColLabels, int *outColCount);
//
///*! \brief Returns Gamma, the conservation law array.
//
//Each row represents a single conservation law where the column indicate the
//participating molecular species. The number of rows is therefore equal to the
//number of conservation laws. Columns are ordered according to the rows in the
//reordered stoichiometry matrix, see ::LibStructural_getReorderedSpeciesId and
//::LibStructural_getReorderedStoichiometryMatrix.
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
// int LibStructural_getGammaMatrix(double** *outMatrix, int* outRows, int *outCols);
//
// int LibStructural_getGammaMatrixGJ(double** inMatrix, int numRows, int numCols,
//                                          double** *outMatrix, int *outRows, int *outCols);
//
// int LibStructural_findPositiveGammaMatrix(double** inMatrix, int numRows, int numCols,
//                const char** inRowLabels,
//                double** *outMatrix, int *outRows, int *outCols,
//                char** *outRowLabels, int *outRowCount);
//
//
///*! \brief Returns the row and column labels for Gamma, the conservation law array.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getGammaMatrixLabels(char** *outRowLabels, int *outRowCount, char** *outColLabels, int *outColCount);
///*! \brief Returns the original, unaltered stoichiometry matrix.
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getStoichiometryMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the row and column labels for the original and unaltered stoichiometry matrix.
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getStoichiometryMatrixLabels(char** *outRowLabels, int *outRowCount, char** *outColLabels, int *outColCount);
///*! \brief Returns the fully reordered stoichiometry matrix (row and column reordered stoichiometry matrix)
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
        //            string test = matrixToString(actual);
//            clog<<test;
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getFullyReorderedStoichiometryMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the reordered stoichiometry matrix (row reordered stoichiometry matrix, columns are not reordered!)
//
//\param outMatrix a pointer to a double array that holds the output
//\param outRows will be overwritten with the number of rows
//\param outCols will be overwritten with the number of columns.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the returned matrix call ::LibStructural_freeMatrix with the outMatrix
//and outRows as parameter.
//*/
//  int LibStructural_getReorderedStoichiometryMatrix(double** *outMatrix, int* outRows, int *outCols);
///*! \brief Returns the row and column labels for the fully reordered stoichiometry matrix (row and column reordered stoichiometry matrix)
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getFullyReorderedStoichiometryMatrixLabels(char** *outRowLabels, int *outRowCount, char** *outColLabels, int *outColCount);
        //            string test = matrixToString(actual);
//            clog<<test;
//
///*! \brief Returns the row and column labels for the reordered stoichiometry matrix (row reordered stoichiometry matrix)
//
//\param outRowLabels a pointer to a string array where the row labels will be allocated
//and written.
//\param outRowCount after the call this variable will hold the number of row labels
//returned.
//\param outColLabels a pointer to a string array where the column labels will be allocated
//and written.
//\param outColCount after the call this variable will hold the number of column labels
//returned.
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks To free the string arrays (outRowLabels and outColLabels) call
//::LibStructural_freeMatrix with the string array and its corresponding length
//(outRowCount or outColCount)
//*/
//  int LibStructural_getReorderedStoichiometryMatrixLabels(char** *outRowLabels, int *outRowCount, char** *outColLabels, int *outColCount);
//
///*! \brief Returns the reordered list of molecular species.
//\param outArray pointer to string array that will be allocated and filled with the species Ids
//\param outLength the number of species
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//*/
//  int LibStructural_getReorderedSpeciesIds(char** *outArray, int *outLength);
//
//
///*! \brief Returns the unordered list of species Ids
//\param outArray pointer to string array that will be allocated and filled with the species Ids
//\param outLength the number of species
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
        //            string test = matrixToString(actual);
//            clog<<test;
//
//*/
//  int LibStructural_getSpeciesIds(char** *outArray, int *outLength);
//
///*! \brief Returns the reordered list of reactions Ids.
//\param outArray pointer to string array that will be allocated and filled with the reordered reaction Ids
//\param outLength the number of species
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int LibStructural_getReorderedReactionIds(char** *outArray, int *outLength);
//
///*! \brief Returns the list of independent species ids.
//\param outArray pointer to string array that will be allocated and filled with the independent species Ids
//\param outLength the number of independent species
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
        //            string test = matrixToString(actual);
//            clog<<test;
//
//*/
//  int LibStructural_getIndependentSpeciesIds(char** *outArray, int *outLength);
//
///*! \brief Returns the list of dependent species Ids.
//\param outArray pointer to string array that will be allocated and filled with the dependent species Ids
//\param outLength the number of dependent species
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//
//*/
//  int LibStructural_getDependentSpeciesIds(char** *outArray, int *outLength);
        //            string test = matrixToString(actual);
//            clog<<test;
//
///*! \brief Returns the list of independent reaction ids.
//\param outArray pointer to string array that will be allocated and filled with the independent reaction Ids
//\param outLength the number of independent reaction
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int LibStructural_getIndependentReactionIds(char** *outArray, int *outLength);
//
///*! \brief Returns the list of dependent reaction Ids.
//\param outArray pointer to string array that will be allocated and filled with the dependent reaction Ids
        //            string test = matrixToString(actual);
//            clog<<test;
//\param outLength the number of dependent reactions
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//
//*/
//  int LibStructural_getDependentReactionIds(char** *outArray, int *outLength);
//
///*! \brief Returns the list of unordered Reactions.
//Returns the original list of reactions in the same order as when it was loaded.
//\param outArray pointer to string array that will be allocated and filled with the reaction Ids
//\param outLength the number of reactions
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int LibStructural_getReactionIds(char** *outArray, int *outLength);
//
///*! \brief Returns algebraic expressions for the conservation laws.
//\param outArray pointer to string array that will be allocated and filled
//\param outLength the number of conservation laws
//\remarks free outArray using ::LibStructural_freeMatrix with the outLength parameter
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int LibStructural_getConservedLaws(char** *outArray, int *outLength);
//
///*! \brief Returns the number of conservation laws.
//\return the number of conservation laws
//*/
//  int LibStructural_getNumConservedSums();
///*! \brief Returns the initial conditions used in the model.
//\param outVariableNames a string vector of all species Ids
//\param outValues a double vector of corresponding initial conditions
//\param outLength number of elements in outVariableNames and outValues (number of species)
//*/
//  int LibStructural_getInitialConditions(char** *outVariableNames, double* *outValues, int *outLength);
//
///*! \brief Validates structural matrices.
//
//Calling this method will run the internal test suite against the structural
//matrices those tests include:\n
//
//\li Test 1 : Gamma*N = 0 (Zero matrix)
//\li Test 2 : Rank(N) using SVD (5) is same as m0 (5)
//\li Test 3 : Rank(NR) using SVD (5) is same as m0 (5)
//\li Test 4 : Rank(NR) using QR (5) is same as m0 (5)
//\li Test 5 : L0 obtained with QR matches Q21*inv(Q11)
//\li Test 6 : N*K = 0 (Zero matrix)
//
//\param outResults an integer vector, each element represents the result for one
//of the above tests (the 0th element representing the test result for test1),
//if the test passed the value is 1 and 0 otherwise.
//\param outLength number of tests
//
//\remarks free outResults using ::LibStructural_freeVector
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int  LibStructural_validateStructuralMatrices(int* *outResults, int* outLength);
///*! \brief Return Details about validation tests.
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//\remarks free outMessage using ::LibStructural_freeVector
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int LibStructural_getTestDetails(char* *outMessage, int *nLength);
//
///*! \brief Returns the name of the model.
//
//Returns the name of the model if SBML model has Name-tag, otherwise it returns the
//SBML id. If only a stoichiometry matrix was loaded 'untitled' will be returned.
//
//\param outMessage a pointer to a string where status information of the analysis
//will be returned.
//\param nLength the length of the message.
//\remarks free outMessage using ::LibStructural_freeVector
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//no stoichiometry matrix was loaded beforehand or none of the analysis methods has
//been called yet.
//
//*/
//  int LibStructural_getModelName(char* *outMessage, int *nLength);
//
////! Returns the total number of species.
//  int LibStructural_getNumSpecies();
//
////! Returns the number of independent species.
        //            string test = matrixToString(actual);
//            clog<<test;
//  int LibStructural_getNumIndSpecies();
//
////! Returns the number of dependent species.
//  int LibStructural_getNumDepSpecies();
////! Returns the total number of reactions.
//  int LibStructural_getNumReactions();
////! Returns the number of independent reactions.
//  int LibStructural_getNumIndReactions();
////! Returns the number of dependent reactions.
//  int LibStructural_getNumDepReactions();
////! Returns the rank of the stoichiometry matrix.
//  int LibStructural_getRank();
////! Returns the percentage of nonzero values in the stoichiometry matrix
//  double LibStructural_getNmatrixSparsity();
        //            string test = matrixToString(actual);
//            clog<<test;
//
///*! \brief Set user specified tolerance
//
//This function sets the tolerance used by the library to determine what value
//is considered as zero. Any value with absolute value smaller than this tolerance is considered as zero
//and will be neglected.
//
//\param dTolerance Sets the tolerance used by the library to determine a  value close to zero
//*/
//  void LibStructural_setTolerance(const double dTolerance);
//
///*! \brief Get user specified tolerance
//
//This function gets the tolerance used by the library to determine what value
//is considered as zero. Any value with absolute value smaller than this tolerance is considered as zero
//and will be neglected.
//
//\return the tolerance used by the library to determine a  value close to zero
//*/
//  double LibStructural_getTolerance();
//
//
////! Frees a vector previously allocated by this library.
// void LibStructural_freeVector(void* vector);
//
////! Frees a matrix previously allocated by this library.
// void LibStructural_freeMatrix(void** matrix, int numRows);
//
////  int LibStructural_getNthReorderedSpeciesId(int n,char* *outMessage, int *nLength);
////  int LibStructural_getNthIndependentSpeciesId(int n,char* *outMessage, int *nLength);
////  int LibStructural_getNthDependentSpeciesId(int n,char* *outMessage, int *nLength);
////  int LibStructural_getNthReactionId(int n,char* *outMessage, int *nLength);
////  int LibStructural_getNthConservedEntity(int n,char* *outMessage, int *nLength);
////  double LibStructural_getNthConservedSum(int n);
//
//} //namespace ..
///*! \brief Returns the currently used tolerance
//
//This function returns the tolerance currently used by the library to determine what value
//is considered as zero. Any value with absolute value smaller than this tolerance is considered zero
//and will be neglected.
//*/
//LIB_EXTERN double LibLA_getTolerance();
//
///*! \brief Set user specified tolerance
//
//This function sets the tolerance used by the library to determine what value
//is considered as zero. Any value with absolute value smaller than this tolerance is considered as zero
//and will be neglected.
//
//\param value Sets the tolerance used by the library to determine a  value close to zero
//*/
//LIB_EXTERN void LibLA_setTolerance(const double value);
//
///*! \brief Calculates the eigen-values of a square real matrix.
//
//This function calculates the complex eigenvalues of the given real matrix. The complex vector
//of eigenvalues will be returned in two real vectors, one for the real and one for the imaginary part.
//
//\param inMatrix real matrix to calculate the eigen-values for.
//\param numRows the number of rows of the input matrix
//\param numCols the number of columns of the input matrix
//\param outReal pointer to the output array for the eigenvalues (real part)
//\param outImag pointer to the output array for the eigenvalues (imaginary part)
//\param outLength the number of eigenvalues written to outReal and outImag
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred (for example because the caller supplied a non-square matrix)
//
//\remarks free outReal and outImag using ::LibLA_freeVector
//
//*/
//LIB_EXTERN int LibLA_getEigenValues(double** inMatrix, int numRows, int numCols, double* *outReal, double * *outImag, int *outLength);
//
///*! \brief Calculates the eigen-values of a square complex matrix.
//
//This function calculates the complex eigenvalues of the given complex matrix. The input matrix
//should be broken up into two matrices representing the real and imaginary parts respectively.
        //            string test = matrixToString(actual);
//            clog<<test;
//The complex vector of eigenvalues will be returned in two  real vectors, one for the real and
//one for the imaginary part.
//
//\param inMatrixReal real part of the complex matrix to calculate the eigen-values for.
//\param inMatrixImag imaginary part of the complex matrix to calculate the eigen-values for
//\param numRows the number of rows of the input matrix
//\param numCols the number of columns of the input matrix
//\param outReal pointer to the output array for the eigenvalues (real part)
//\param outImag pointer to the output array for the eigenvalues (imaginary part)
//\param outLength the number of eigenvalues written to outReal and outImag
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred (for example non square matrix)
//
//\remarks free outReal and outImag using ::LibLA_freeVector
//
//*/
//LIB_EXTERN int LibLA_ZgetEigenValues(double** inMatrixReal, double** inMatrixImag, int numRows, int numCols, double* *outReal, double * *outImag, int *outLength);
//
///*!    \brief This function computes the QR factorization of the given real M-by-N matrix A with column pivoting.
//
        //            string test = matrixToString(actual);
//            clog<<test;
//The LAPACK method dgeqp3 is used followed by an orthonormalization of Q through the use of DORGQR.
//The factorized form is:
//
//\par
//A = Q * R
//
//this method also returns the column pivots used in the P matrix.
//
//\param inMatrix real matrix to factorize
//\param numRows number of rows of the matrix
//\param numCols number of columns of the matrix
//\param outQ pointer to a real matrix where Q will be written
//\param outQRows number of rows of the Q matrix
//\param outQCols number of columns of the Q matrix
//\param outR pointer to a real matrix where R will be written
//\param outRRows number of rows of the R matrix
//\param outRCols number of columns of the R matrix
//\param outP pointer to a real matrix where P will be written
        //            string test = matrixToString(actual);
//            clog<<test;
//\param outPRows number of rows of the P matrix
//\param outPCols number of columns of the P matrix
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred
//
//\remarks free outP, outQ and outR using ::LibLA_freeMatrix
//
//*/
//LIB_EXTERN int LibLA_getQRWithPivot(double** inMatrix, int numRows, int numCols,
//                                    double** *outQ, int *outQRows, int * outQCols,
//                                    double** *outR, int *outRRows, int * outRCols,
//                                    double** *outP, int *outPRows, int * outPCols);
//
///*!    \brief This function computes the QR factorization of the given real M-by-N matrix A with column pivoting.
        //            string test = matrixToString(actual);
//            clog<<test;
//
//The LAPACK method dgeqp3 is used followed by an orthonormalization of Q through the use of DORGQR.
//The factorized form is:
//
//\par
//A = Q * R
//
//\param inMatrix real matrix to factorize
//\param numRows number of rows of the matrix
//\param numCols number of columns of the matrix
//\param outQ pointer to a real matrix where Q will be written
//\param outQRows number of rows of the Q matrix
//\param outQCols number of columns of the Q matrix
//\param outR pointer to a real matrix where R will be written
//\param outRRows number of rows of the R matrix
//\param outRCols number of columns of the R matrix
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred
//
//\remarks free outQ and outR using ::LibLA_freeMatrix
//
//*/
//LIB_EXTERN int LibLA_getQR(double** inMatrix, int numRows, int numCols,
//                           double** *outQ, int *outQRows, int * outQCols,
//                           double** *outR, int *outRRows, int * outRCols);
//
///*! \brief This method performs the Singular Value Decomposition of the given real matrix, returning only the singular values.
//
//This procedure is carried out by the LAPACK method dgesdd.
//
//\param inMatrix real matrix
//\param numRows number of rows of the matrix
//\param numCols number of columns of the matrix
        //            string test = matrixToString(actual);
//            clog<<test;
//
//\param outSingularVals pointer to the double array where the singular values will be stored
//\param outLength number of singular values
//
//\return The return value will be zero (0) when successful, and negative (-1) in case
//an error occurred
//
//\remarks free outSingularVals using ::LibLA_freeVector
//*/
//
//LIB_EXTERN int LibLA_getSingularValsBySVD(double** inMatrix, int numRows, int numCols, double* *outSingularVals, int *outLength);
//
///*! \brief This function computes the LU factorization of the given real N-by-N matrix A using complete pivoting (with row and column interchanges).
//
//This procedure is carried out by the LAPACK method dgetc2.
//
//A is factorized into:
//
//\par
//A = P * L * U * Q
//
//Here P and Q are permutation matrices for the rows and columns respectively.
//
//\remarks This function supports only square matrices (N-by-N), choose ::LibLA_getQRWithPivot for a stable method
//operating on N-by-M matrices.
//*/
//LIB_EXTERN int LibLA_getLUwithFullPivoting(double** inMatrix, int numRows, int numCols,
//                                           double** *outL, int *outLRows, int * outLCols,
//                                           double** *outU, int *outURows, int * outUCols,
//                                           int** *outP, int *outPRows, int * outPCols,
//                                           int** *outQ, int *outQRows, int * outQCols,
//                                           int *info);
//
///*! \brief This function computes the LU factorization of the given real M-by-N matrix A
//
        //            string test = matrixToString(actual);
//            clog<<test;
//using partial pivoting with row interchanges. This procedure is carried out by the
//LAPACK method dgetrf.
//
//A is factorized into:
//
//\par
//A = P * L * U
//
//Here P is the row permutation matrix.
//*/
//LIB_EXTERN int LibLA_getLU(double** inMatrix, int numRows, int numCols,
//                           double** *outL, int *outLRows, int * outLCols,
//                           double** *outU, int *outURows, int * outUCols,
//                           int** *outP, int *outPRows, int * outPCols,
//                           int *info);
//
///*! \brief This function calculates the inverse of a square real matrix.
//
//This procedure is carried out by the LAPACK methods dgetrf and dgetri. This means that the matrix will be
//factorized using LU decomposition first, followed by the calculation of the inverse based on:
//
//\par
//inv(A)*L = inv(U) for inv(A).
//*/
//LIB_EXTERN int LibLA_inverse(double** inMatrix, int numRows, int numCols,
//                             double** *outMatrix, int *outRows, int *outCols);
//
///*! \brief This function calculates the left null space of a given real matrix.
//
//That is:
//\par
//null(A)*A = 0
//
//\remarks This function is equivalent to returning the right null space of the transposed matrix.
//See ::LibLA_rightNullspace
//*/
//LIB_EXTERN int LibLA_leftNullspace(double** inMatrix, int numRows, int numCols,
//                                   double** *outMatrix, int *outRows, int *outCols);
//
///*! \brief This function calculates the right null space of a given real matrix.
//
//That is:
//
//\par
//A*null(A) = 0
//
//In order to calculate the (right) null space, we first calculate the full singular value decomposition (employing dgesdd) of the matrix:
//
//\par
//[U,S,V] = svd(A');
//
//then calculate the rank:
//
//\par
//r = rank(A)
//
//and finally return the last columns of the U matrix (r+1...n) as the null space matrix.
//*/
//LIB_EXTERN int LibLA_rightNullspace(double** inMatrix, int numRows, int numCols,
//                                    double** *outMatrix, int *outRows, int *outCols);
//
///*! \brief This function calculates the scaled left null space of a given real matrix.
//
//This function is equivalent to calling ::LibLA_leftNullspace however the resulting
//matrix will be scaled (employing Gauss Jordan factorization) to yield whole numbered
//entries wherever possible.
//*/
//LIB_EXTERN int LibLA_scaledLeftNullspace(double** inMatrix, int numRows, int numCols,
//                                         double** *outMatrix, int *outRows, int *outCols);
//
///*! \brief This function calculates the scaled right null space of a given real matrix.
//
//This function is equivalent to calling ::LibLA_rightNullspace however the resulting
//matrix will be scaled (employing Gauss Jordan factorization) to yield whole numbered
//entries wherever possible.
//*/
//LIB_EXTERN int LibLA_scaledRightNullspace(double** inMatrix, int numRows, int numCols,
//                                          double** *outMatrix, int *outRows, int *outCols);
//
//
///*! \brief This method computes the rank of the given matrix.
//
//The singular values of the matrix are calculated and the rank is determined by the number of non-zero values.
//
//Note that zero here is defined as any value whose absolute value is bigger than the set tolerance (see
//::LibLA_setTolerance )
//*/
//LIB_EXTERN int LibLA_getRank(double** inMatrix, int numRows, int numCols);
//
///*! \brief  reciprocal condition number estimate
//
//returns an estimate for the reciprocal of the condition of A in 1-norm using the LAPACK condition estimator.
//If A is well conditioned, getRCond(A) is near 1.0. If A is badly conditioned, getRCond(A) is near 0.0.
//
//*/
//LIB_EXTERN double LibLA_getRCond(double** inMatrix, int numRows, int numCols);
//
///*! \brief This method calculates the Gauss Jordan or row echelon form of the given matrix.
//
//Only row swaps are used. These permutations will be returned in the 'pivots' vector.
        //            string test = matrixToString(actual);
//            clog<<test;
//
//If no permutations have occurred this vector will be in ascending form [ 0, 1, 2, 3 ];
//However if say row one and three would be swapped this vector would look like: [ 0, 3, 2, 1 ];
//
//*/
//LIB_EXTERN int LibLA_gaussJordan(double** inMatrix, int numRows, int numCols,
//                                 double** *outMatrix, int *outRows, int *outCols,
//                                 int* *oPivots, int *nLength);
//
///*! \brief This method calculates the fully pivoted Gauss Jordan form of the given matrix.
//
//Fully pivoted means, that rows as well as column swaps will be used. These permutations
//are captured in the integer vectors rowPivots and colPivots.
//
//If no permutations have occurred those vectors will be in ascending form [ 0, 1, 2, 3 ];
//However if say row one and three would be swapped this vector would look like: [ 0, 3, 2, 1 ];
//*/
//LIB_EXTERN int LibLA_fullyPivotedGaussJordan(double** inMatrix, int numRows, int numCols,
//                                             double** *outMatrix, int *outRows, int *outCols,
//                                             int* *oRowPivots, int *nRowLength,
//                                             int* *oColPivots, int *nColLength);
//
//
//
///*! \brief This function calculates the inverse of a square complex matrix.
//
//This procedure is carried out by the LAPACK methods: zgetrf and zgetri. This means that the matrix will be
//factorized using LU decomposition first, followed by the calculation of the inverse based on:
//
//\par
//inv(A)*L = inv(U) for inv(A).
//*/
//LIB_EXTERN int LibLA_Zinverse(double** inMatrixReal, double **inMatrixImag, int numRows, int numCols,
//                              double** *outMatrixReal, double ** *outMatrixImag, int *outRows, int *outCols);
//
////! Frees a vector previously allocated by this library.
//LIB_EXTERN void LibLA_freeVector(void* vector);
//
////! Frees a matrix previously allocated by this library.
//LIB_EXTERN void LibLA_freeMatrix(void** matrix, int numRows);
//
//
///*! \brief Factorizes the given matrix using SVD
//
//This function computes the singular value decomposition (SVD) of the given real matrix.
//
//
//The SVD is written
//
//\par
//A = U * SIGMA * transpose(V)
//
//\remarks this function returns the transpose of V
//
//*/
//LIB_EXTERN int LibLA_getSVD(double** inMatrix, int numRows, int numCols,
//                       double** *outU, int *outRowsU, int *outColsU,
//                       double* *outSingVals, int *outLength,
//                       double** *outV, int *outRowsV, int *outColsV);
//
///*! \brief Factorizes the given matrix using SVD
//
//This function computes the singular value decomposition (SVD) of the given complex matrix.
//
//
//The SVD is written
//
//\par
//A = U * SIGMA * conjugate-transpose(V)
//
//\remarks this function returns the conjugate-transpose of V
//
//*/
//LIB_EXTERN int LibLA_ZgetSVD(double** inMatrixReal, double** inMatrixImag, int numRows, int numCols,
//                       double** *outUReal, double** *outUImag, int *outRowsU, int *outColsU,
//                       double* *outSingVals, int *outLength,
//                       double** *outVReal, double** *outVImag, int *outRowsV, int *outColsV);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#endif //Header guard

