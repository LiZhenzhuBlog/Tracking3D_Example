/*****************************************************************
Name:               ProgramOptions.h

Description:	This header file is used for the set ProgramOptions
				dialog.

All Northern Digital Inc. ("NDI") Media and/or Sample Code and/or
Sample Code Documentation (collectively referred to as "Sample Code")
is licensed and provided "as is" without warranty of any kind.  The
licensee, by use of the Sample Code, warrants to NDI that the Sample
Code is fit for the use and purpose for which the licensee intends to
use the Sample Code. NDI makes no warranties, express or implied, that
the functions contained in the Sample Code will meet the licensee�s
requirements or that the operation of the programs contained therein
will be error free.  This warranty as expressed herein is exclusive
and NDI expressly disclaims any and all express and/or implied, in fact
or in law, warranties, representations, and conditions of every kind
pertaining in any way to the Sample Code licensed and provided by NDI
hereunder, including without limitation, each warranty and/or condition
of quality, merchantability, description, operation, adequacy,
suitability, fitness for particular purpose, title, interference with
use or enjoyment, and/or non infringement, whether express or implied
by statute, common law, usage of trade, course of dealing, custom, or
otherwise.  No NDI dealer, distributor, agent or employee is authorized
to make any modification or addition to this warranty.

In no event shall NDI nor any of its employees be liable for any direct,
indirect, incidental, special, exemplary, or consequential damages,
sundry damages or any damages whatsoever, including, but not limited to,
procurement of substitute goods or services, loss of use, data or profits,
or business interruption, however caused.  In no event shall NDI�s
liability to the licensee exceed the amount paid by the licensee for the S
ample Code or any NDI products that accompany the Sample Code. The said
imitations and exclusions of liability shall apply whether or not any
such damages are construed as arising from a breach of a representation,
warranty, guarantee, covenant, obligation, condition or fundamental term
or on any theory of liability, whether in contract, strict liability, or
tort (including negligence or otherwise) arising in any way out of the
use of the Sample Code even if advised of the possibility of such damage.
In no event shall NDI be liable for any claims, losses, damages, judgments,
costs, awards, expenses or liabilities of any kind whatsoever arising
directly or indirectly from any injury to person or property, arising
from the Sample Code or any use thereof.


Copyright (C) 2002, 2003, Northern Digital Inc. All rights reserved.


*****************************************************************/
#if !defined(AFX_PROGRAMOPTIONS_H__104B855B_0B91_4F65_9145_B4A48ED63156__INCLUDED_)
#define AFX_PROGRAMOPTIONS_H__104B855B_0B91_4F65_9145_B4A48ED63156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgramOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgramOptions dialog

class CProgramOptions : public CDialog
{
// Construction
public:
	CProgramOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgramOptions)
	enum { IDD = IDD_PROGRAM_OPTIONS };
	BOOL	m_bBeepOnError;
	BOOL	m_bBeepOnWarning;
	BOOL	m_bClearLogFile;
	BOOL	m_bDateTimeStampFile;
	CString	m_szLogFile;
	BOOL	m_bLogToFile;
	int		m_nNoErrorBeeps;
	int		m_nNoWarningBeeps;
	BOOL	m_bReportWhileTracking;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgramOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgramOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLogToFile();
	afx_msg void OnBeepError();
	afx_msg void OnBeepOnWarning();
	afx_msg void OnBrowse();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void FillForm();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMOPTIONS_H__104B855B_0B91_4F65_9145_B4A48ED63156__INCLUDED_)
/************************END OF FILE*****************************/
