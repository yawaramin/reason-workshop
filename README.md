# ReasonML React Workshop

In this project, we will build a simple ReasonReact application using the
ReasonReact router. We'll see how the router's design encourages us to
keep the current route synchronised with our app's current state.

Then, we'll see how to fix an issue where our app's state gets out of
sync with the route.

## Setup

You will need at least:

- npm
- Visual Studio Code or another editor if you're confident you can set up
  ReasonML support in that editor
- The `vscode-reasonml` extension for VSCode

After installing the above, run the following:

    npm install
    bsb -make-world
    parcel index.html

Then open http://localhost:1234
