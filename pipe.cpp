#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main( string cmd, vector<string> &argv, int argc,
    vector<int> &redirect)
{
    int result = 0, pid, /* some other declarations */;
    bool file_in, file_out, pipe_in, pipe_out;
    queue<int*> pipes; // never has more than 2 pipes

    // parse, fork, exec, & loop if there's a pipe until no more pipes
    do
    {
        /* some declarations for variables used in parsing */
        file_in = file_out = pipe_in = pipe_out = false;

        // parse the next command and set some flags
        while( /* there's more redirection */ )
        {
            string symbol = /* next redirection symbol */

            if( symbol == ">" )
            {
                /* set flags, get filename, etc */
            }   
            else if( symbol == "<" )
            {
                /* set flags, get filename, etc */
            }
            else if( pipe_out = (symbol == "|") )
            {
                    /* set flags, and... */
                int tempPipes[2];               
                pipes.push( pipe(tempPipes) );
                break;
            }
        }

        /* ... set some more flags ... */

        // fork child
        pid = fork();
        if( pid == 0 )  // child
        {
            /* if pipe_in and pipe_out set, there are two pipes in queue. 
            the old pipes read  is dup'd to stdin, and the new pipes
            write is dup'd to stdout, other two FD's are closed */

            /* if only pipe_in or pipe_out, there is one pipe in queue.
            the unused end is closed in whichever if statement evaluates */

            /* if neither pipe_in or pipe_out is set, no pipe in queue */

            // redirect stdout
            if( pipe_out ){
                // close newest pipes read end
                close( pipes.back()[P_READ] );

                // dup the newest pipes write end
                dup2( pipes.back()[P_WRITE], STDOUT_FILENO );

                // close newest pipes write end
                close( pipes.back()[P_WRITE] );
            }
            else if( file_out ) 
                freopen(outfile.c_str(), "w", stdout);

            // redirect stdin
            if( pipe_in ){
                close( pipes.front()[P_WRITE] );
                dup2( pipes.front()[P_READ], STDIN_FILENO );
                close( pipes.front()[P_READ] );
            }
            else if ( file_in ) 
                freopen(infile.c_str(), "r", stdin);


            // create argument list and exec
            char **arglist = make_arglist( argv, start, end );
            execv( cmd.c_str(), arglist );

            cout << "Execution failed." << endl;    
            exit(-1); // this only executes is execv fails

        }   // end child

        /* close the newest pipes write end because child is writing to it.
           the older pipes write end is closed already */
        if( pipe_out ) 
            close( pipes.back()[P_WRITE] );

        // remove pipes that have been read from front of queue
        if( init_count > 0 )    
        {
            close( pipes.front()[P_READ] ); // close FD first
            pipes.pop();                    // pop from queue
        }   

    } while ( pipe_out );

    // wait for each child process to die

    return result;
}
