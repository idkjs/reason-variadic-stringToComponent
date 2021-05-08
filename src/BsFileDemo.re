let str = React.string;

open FileRe;

type state = {files: array(File.t)};

type action =
  | ChangeFile(File.t)
  | Upload;

[@react.component]
let make = _ => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ChangeFile(file) => {files: [|file|]}
        | Upload =>
          Js.log("upload");
          let data = FormData.make();
          FormData.appendFile(data, "avatar", state.files[0]);
          FormData.appendString(data, "filename", "santaduck");

          Js.log(FormData.get(data, "avatar"));
          Js.log(FormData.get(data, "filename"));

          Js.Promise.(
            Fetch.fetchWithInit(
              "http://localhost:8080/profile",
              Fetch.RequestInit.make(
                ~method_=Post,
                ~body=Fetch.BodyInit.makeWithFormData(data),
                (),
              ),
            )
            |> then_(Fetch.Response.json)
            |> ignore
          );
          {files: [||]};
        },
      {files: [||]},
    );

  let upload = _event => dispatch(Upload);
  let changeFile = event => {
    let files = ReactEvent.Form.target(event)##files;
    dispatch(ChangeFile(files[0]));
  };

  Js.log(state);
  <div>
    <h1> {"bs-file" |> str} </h1>
    <p> {"open the console (CMD + C) to view logs" |> str} </p>
    <input type_="file" onChange={e => changeFile(e)} />
    <div id="preview" />
    <button onClick={e => upload(e)}> {"Upload" |> str} </button>
    Variadic.make
    <Root />
    // <RootSpreadDoesntWork />
  </div>;
};
