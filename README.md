# CiS-G

CiS-G is a simple static site generator written in C. It processes markdown files 
from the `content` directory, applies templates from the `templates` directory, and 
outputs the generated HTML files to the `output` directory.

## Features

- Processes markdown (currently supports only test files) files and converts them into HTML.
- Applies a specified HTML template to the content files.
- Outputs the generated HTML files to a specified directory.
- Supports both Windows and Unix-like systems.

## Directory Structure

```
CiS-G/
├── content/
│ └── example.md
├── templates/
│ └── template.html
├── output/
├── ssg.c
└── README.md
```

## Building and Running

### Prerequisites

- A C compiler (e.g., `gcc` on Linux or MinGW on Windows)

### Building

To compile the static site generator, run:
```bash
gcc -o ssg ssg.c
```

## Running

To generate the static site, run:
```bash
./ssg content templates output
```

## Error Handling

If you encounter an error such as "Error opening file: No such file or directory", 
ensure that your directory structure matches the example above and that the paths to 
the content and template files are correct.

## Example Content and Template

### Example Markdown (content/example.md)

Title: My Book Review
Heading: A Great Read
Paragraph: This book was an excellent journey through the world of C programming. Highly recommended!

### Example HTML Template (templates/template.html)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{{ title }}</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
            background-color: #f0f0f0;
        }
        .review {
            max-width: 800px;
            margin: auto;
            background: #fff;
            padding: 20px;
            border-radius: 5px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }
        .review h2 {
            color: #333;
            font-size: 28px;
            margin-bottom: 10px;
        }
        .review p {
            color: #666;
            font-size: 16px;
            line-height: 1.8;
        }
    </style>
</head>
<body>
    <div class="review">
        <h2>{{ heading }}</h2>
        <p>{{ paragraph }}</p>
    </div>
</body>
</html>
```

## License

This project is licensed under the MIT License.

## Sample Content File and Template

The content and template provided in the README are designed to work together. When you run `./ssg content templates output`, 
the markdown content will be embedded into the HTML template, resulting in styled HTML output. 

Ensure the paths and file names in your actual implementation match those given in the README for a seamless experience. 
Adjust paths and details as needed based on your project setup and requirements.
