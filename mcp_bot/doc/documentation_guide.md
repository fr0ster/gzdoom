# GZDoom Documentation Guide

This guide provides instructions for maintaining and expanding the documentation for the GZDoom source code. The documentation is stored in the `mcp_bot/doc/src` directory, which mirrors the structure of the `src` directory.

## Documentation Status

As of the current analysis, there are **985 missing documentation files** across various directories. The most affected directories include:

1. `playsim`: 68 files
2. `common\utility`: 53 files
3. `common\platform\win32`: 32 files
4. `common\rendering\hwrenderer\data`: 31 files
5. `common\textures`: 30 files

For a complete analysis, see the [Documentation Status Report](documentation_status_report.md).

## Documentation Format

Each source file in the `src` directory should have a corresponding documentation file in the `mcp_bot/doc/src` directory:

- For `.cpp` files: `filename.md`
- For `.h` files: `filename_h.md`

### Documentation Template

Each documentation file should follow this structure:

```markdown
# [filename].[extension]

## File Purpose
[Brief description of what the file does and its role in the codebase]

## Key Components
[List and describe major classes, structures, enumerations, and other important elements]

### [Component Name]
[Detailed description of the component]

## [Technical/Implementation] Details
[More specific information about how things are implemented]

## Connections with Other Modules
[How this file interacts with other parts of the codebase]
```

For header files, focus on the interface and usage. For implementation files, focus on the implementation details.

## Documentation Tools

### Documentation Template Generator

The `generate_doc_templates.py` script helps identify missing documentation files and generate templates for them:

```bash
# List all missing documentation files
python generate_doc_templates.py --list

# Generate templates for all missing documentation files
python generate_doc_templates.py --generate

# Generate templates for a specific directory
python generate_doc_templates.py --generate --dir common/utility
```

### Documentation Process

1. **Identify Missing Documentation**: Use the script to identify files that need documentation.
2. **Analyze the Source File**: Read and understand the source file to document.
3. **Create Documentation**: Write documentation following the template format.
4. **Review and Refine**: Ensure the documentation is accurate and comprehensive.

## Documentation Guidelines

### File Purpose
- Clearly explain what the file does and its role in the codebase
- Mention any design patterns or architectural principles used

### Key Components
- Document all major classes, structures, enumerations, and functions
- Explain the purpose and functionality of each component
- For complex components, provide examples of usage if applicable

### Implementation Details
- Explain how the functionality is implemented
- Highlight any algorithms, optimizations, or special techniques used
- Document any non-obvious behavior or edge cases

### Connections with Other Modules
- List all header files included and explain their relationship
- Describe how this file interacts with other parts of the codebase
- Mention any dependencies or requirements

## Example Documentation

See [sample_documentation_a_action.md](sample_documentation_a_action.md) for an example of a well-documented file.

## Best Practices

1. **Be Concise**: Write clear, concise documentation that focuses on the important aspects.
2. **Be Accurate**: Ensure the documentation accurately reflects the current state of the code.
3. **Be Comprehensive**: Cover all major components and functionality.
4. **Use Sections**: Organize the documentation into logical sections for better readability.
5. **Update Regularly**: Keep the documentation up-to-date as the code changes.

## Prioritization Strategy

1. Start with the most critical directories (those with the most missing files).
2. Focus on core functionality first, then move to peripheral features.
3. Document header files before implementation files to establish the interface.
4. Prioritize files that are frequently modified or referenced.

By following this guide, you can help improve the documentation coverage and quality for the GZDoom codebase, making it more accessible and maintainable for all developers.
