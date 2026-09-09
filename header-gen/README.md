# ML Model Header Generator

## Instructions

Install dependencies:

```bash
npm install
```

Change the header data in `input.data.ts and run the script:

```bash
npm run start
```

The data converted as a C array and DeviceScript hex template literal
will be printed to console.

## Releasing

Create a GitHub release tagged `header-gen-vX.Y.Z`. The version comes from the
tag. The workflow stages the package on npm via trusted publishing and a
maintainer approves it with `npm stage approve`. Plain `vX.Y.Z` tags are the
MakeCode extension's and do not publish this package.
