module React = ReasonReact;
module ReactDOM = ReactDOMRe;

ReactDOM.renderToElementWithId(
  <p>(React.stringToElement("Hello, World!"))</p>,
  "index");
