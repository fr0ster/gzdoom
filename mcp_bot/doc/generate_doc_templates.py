#!/usr/bin/env python3
"""
Documentation Template Generator for GZDoom

This script identifies source files in the src directory that don't have
corresponding documentation files in mcp_bot/doc/src, and generates
template documentation files for them.
"""

import os
import sys
import argparse
from pathlib import Path

# Templates for documentation files
CPP_TEMPLATE = """# {filename}

## File Purpose
[Brief description of what this file does and its role in the codebase]

## Key Components

### [Component Name]
[Description of major classes, functions, or other important elements]

## Implementation Details
[Specific information about how the functionality is implemented]

## Connections with Other Modules
[How this file interacts with other parts of the codebase]
"""

H_TEMPLATE = """# {filename}

## File Purpose
[Brief description of what this header file defines and its role in the codebase]

## Key Components

### [Class/Structure/Enum Name]
[Description of the class/structure/enum and its purpose]

#### [Methods/Members]
[Description of important methods or members]

## Usage
[How to use the functionality provided by this header]

## Connections with Other Modules
[How this file interacts with other parts of the codebase]
"""

def ensure_dir_exists(directory):
    """Ensure that a directory exists, creating it if necessary."""
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f"Created directory: {directory}")

def generate_doc_template(src_file, doc_file, is_header):
    """Generate a documentation template file for a source file."""
    template = H_TEMPLATE if is_header else CPP_TEMPLATE
    content = template.format(filename=os.path.basename(src_file))
    
    # Ensure the directory exists
    doc_dir = os.path.dirname(doc_file)
    ensure_dir_exists(doc_dir)
    
    # Write the template to the file
    with open(doc_file, 'w') as f:
        f.write(content)
    
    return doc_file

def find_missing_docs(src_root, doc_root, generate=False, specific_dir=None):
    """Find source files that don't have corresponding documentation files."""
    missing_docs = []
    
    # Walk through the src directory
    for root, dirs, files in os.walk(src_root):
        # Get the relative path from src_root
        rel_path = os.path.relpath(root, src_root)
        
        # Skip if not in the specific directory (if specified)
        if specific_dir and not (rel_path == specific_dir or rel_path.startswith(specific_dir + os.sep)):
            continue
            
        if rel_path == '.':
            rel_path = ''
            
        # Check if the corresponding doc directory exists
        doc_dir = os.path.join(doc_root, rel_path)
        if not os.path.isdir(doc_dir) and rel_path != '':
            ensure_dir_exists(doc_dir)
            
        # Check each file in the current directory
        for file in files:
            if file == 'CMakeLists.txt':
                continue
                
            # Skip directories
            if os.path.isdir(os.path.join(root, file)):
                continue
                
            # Only process .cpp and .h files
            if not (file.endswith('.cpp') or file.endswith('.h')):
                continue
                
            # Determine the expected doc filename
            is_header = file.endswith('.h')
            if is_header:
                expected_doc = file[:-2] + '_h.md'
            else:
                expected_doc = file[:-4] + '.md'
                
            # Check if the doc file exists
            doc_path = os.path.join(doc_dir, expected_doc)
            if not os.path.isfile(doc_path):
                src_path = os.path.join(root, file)
                missing_docs.append((src_path, doc_path, is_header))
                
                # Generate the template if requested
                if generate:
                    generated_file = generate_doc_template(src_path, doc_path, is_header)
                    print(f"Generated template: {generated_file}")
    
    return missing_docs

def main():
    parser = argparse.ArgumentParser(description='Generate documentation templates for GZDoom source files.')
    parser.add_argument('--src', default='src', help='Source directory (default: src)')
    parser.add_argument('--doc', default='mcp_bot/doc/src', help='Documentation directory (default: mcp_bot/doc/src)')
    parser.add_argument('--generate', action='store_true', help='Generate template files for missing documentation')
    parser.add_argument('--dir', help='Specific directory to process (relative to src)')
    parser.add_argument('--list', action='store_true', help='List missing documentation files without generating templates')
    
    args = parser.parse_args()
    
    # Find missing documentation files
    missing_docs = find_missing_docs(args.src, args.doc, args.generate, args.dir)
    
    # If not generating templates, print the list of missing files
    if args.list or not args.generate:
        print(f"Missing documentation for {len(missing_docs)} files:")
        for src_path, doc_path, _ in missing_docs:
            rel_src = os.path.relpath(src_path, args.src)
            print(f"- {rel_src}")
    
    # Print summary
    print(f"\nTotal missing documentation files: {len(missing_docs)}")
    if args.generate:
        print(f"Generated {len(missing_docs)} template files.")

if __name__ == "__main__":
    main()
