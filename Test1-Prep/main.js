const { exec } = require('child_process');
const fs = require('fs');
fs.writeFileSync('main.py', 'print("Hello World!"');
exec('python main.py', (error, stdout, stderr) => {console.log(stdout);});