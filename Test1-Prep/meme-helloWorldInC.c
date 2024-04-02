#include <stdio.h>
#include <stdlib.h>

char string[] =
"const { exec } = require(\'child_process\');\n"
"const fs = require(\'fs\');\n"
"fs.writeFileSync(\'main.py\', \'print(\"Hello World!\"\');\n"
"exec(\'python main.py\', (error, stdout, stderr) => {console.log(stdout);});";

int main(int argc, char ** kwargs) {
    FILE *file = fopen("main.js", "w");
    fprintf(file, string);
    fclose(file);
    system("node main.js");
    return 0;
}
