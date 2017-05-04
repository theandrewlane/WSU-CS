/*
 *  nocomment.jflex: template to print all numbers not in C-style comments
 *  Andrew Lane
 *  CS4110
 */
%%

%public
%class nocomment
%standalone

NUMBER	 = ([0-9]+"."([0-9]*)?)|("."[0-9]+)|([0-9]+)
LineTerminator = \r|\n|\r\n
InputCharacter = [^\r\n]


/* comments */
Comment = {TraditionalComment} | {EndOfLineComment} | {DocumentationComment}
TraditionalComment   = "/*" [^*] ~"*/" | "/*" "*"+ "/"
EndOfLineComment     = "//" {InputCharacter}* {LineTerminator}?
DocumentationComment = "/**" {CommentContent} "*"+ "/"
CommentContent       = ( [^*] | \*+ [^/*] )*
startComment = "/*"
endComment = "*/"


%{
	int numberCount = 0;
	int commentedNumberCount = 0;
	int enterComment = 0;
%}


%eof{
	numberCount = numberCount - commentedNumberCount;
	System.out.println("Number count: " + numberCount);
	System.out.println("Commented number count: " + commentedNumberCount);
	
%eof}

%state InComment
%%



<YYINITIAL>
{

{NUMBER}  {
numberCount++;
}

{startComment} {
yybegin(InComment);
}

}


<InComment> {

{NUMBER} 
		{
	
		    numberCount++;
		    commentedNumberCount++;
		
		}
{endComment}	{

	    yybegin(YYINITIAL);
	
}	


}

/* ignore whitespace */
[ \t\n]+	{ }

/* ignore all else */

.	{ }





			