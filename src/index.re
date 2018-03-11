module React = ReasonReact;
module ReactDOM = ReactDOMRe;
module Event = ReactEventRe;
let echo = React.stringToElement;

module Button = {
  let component = React.statelessComponent("Button");
  let make(~onClick, children) = {
    ...component,
    render: (_) => <a className="button is-rounded" href="#" onClick>
      (React.arrayToElement(children))
    </a>
  };
};

module ReasonDemo = {
  type action = GotoIndex | GotoId(int) | Alert(string);

  [@bs.val] external alert: string => unit = "";
  let component = React.reducerComponent("ReasonDemo");
  let initialState() = None;

  let reducer(action, _) = switch (action) {
  | Alert(string) => React.SideEffects((_) => {
      alert(string);
      React.Router.push("/index")
    })
  | GotoId(int) => React.Update(Some(int))
  | GotoIndex => React.Update(None)
  };

  let subscriptions({React.send}) = [
    React.Sub(
      () => React.Router.watchUrl(url => switch (url.path) {
        | ["goto", id] => try (send(GotoId(int_of_string(id)))) {
          | Failure(_) => ()
          }
        | ["index"] => send(GotoIndex)
        | _ => send(Alert("Danger, Will Robinson!"))
      }),
      React.Router.unwatchUrl)
  ];

  let route(path, event) = {
    Event.Mouse.preventDefault(event);
    React.Router.push(path)
  };

  let render({React.state}) = switch (state) {
  | None => <div>
    <h1 className="title">(echo("ReasonML React Demo"))</h1>
    <Button onClick=route("/goto/1")>(echo({j|Goto 1 ➡️|j}))</Button>
    <Button onClick=route("/goto/2")>(echo({j|Goto 2 ➡️|j}))</Button>
    <Button onClick=route("/alert")>(echo({j|Alert ⚠️|j}))</Button>
    </div>
  | Some(id) => <div>
      <h1 className="title">
        (echo({j|You're looking at ID $id! 😊|j}))
      </h1>
      <p>
        <Button onClick=route("/index")>
          (echo({j|⬅️ Goto index️|j}))
        </Button>
      </p>
    </div>
  };

  let make(_) = {
    ...component,
    initialState,
    reducer,
    subscriptions,
    render
  };
};

ReactDOM.renderToElementWithId(<ReasonDemo />, "index");
