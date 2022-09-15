/* format output is the core io component in c lang, actually, c lang doesn't have plentiful resources, and therefore we should learn detailedly these quite basic components and make full use of them. 
 * 
 * Skillful ability of the format lib can give a better understanding of it and make we strong in debug. 
 */ 

#include <stdio.h> 
// include macro is used to quote the related source codes. 

// int printf (const char *, ...); 
// Actually, we just want the declare of func `printf`, but it's included in <stdio.h> file. 

int main(void ) {
    printf ("Call printf (\"Hello World\\n\"); \n\n"); 
    // If you have some experience on other langs, you would be surprised that we call this func but do not care its returning value. '\n' backslash alongs with 'n' would express a new line. 

    // printf ("%d", '\''); 
    // return 2; 

    {
        char const *str = "char const *str = %c%s%c; %cprintf (str, 34, str, 34, 10, 10); %c"; 
        printf (str, 34, str, 34, 10, 10);      
    }
    puts(""); 
    // This is a simple & hack quine. hhh 
    // You have no need to know the magic number meaning, but I just use it to show the format power. 

    //tutorial: %s rule 
    {
        const char x[] = "Hello World!\n";
        printf ("%s", x); 
        // %s means the char[] object, which means a countinuous char array, (use null terminated rule) print the entire content out. 

        printf ("%20s", x); 
        // You can also add a speical number between % and 's', to make the print out with a specific size! 
        // If the size is smaller than itself, that the size you determine would be ignored; if it's bigger, the default layout is right aligned. 
    }

    // tutorial: %c rule 
    {
        char t = 'K'; 
        printf ("What's your opinion about: %c%c%c? \n", t, t, t); 
        // %c is used to describe a char type object. 

        t = 'x'; 
        printf ("What's your opinion about: %c%c%c? \n", t, t, t); 
        // Changes the content in t, and then you can see the changing on the output. 

        printf ("What's your opinion about: %2c%2c%2c? \n", t, t, t); 
        // It's quite simple, but you can still add some special number on it, to make it wide~ 
    }

    // tutorial: %d rule 
    {
        // Actually %d is only used to determine the type 'int'. 
        // The domain isn't ensured when you use int in different computers. Most are 32 bits, but some are still 16 bits. 
        int age = 18; 
        printf ("What's your age? \n\tMy name is %d. \n", age); 
    }

}