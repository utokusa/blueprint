import React, { Component, PropsWithChildren } from 'react';

export interface InputEvent {
  value: string
}

export interface ChangeEvent {
  value: string
}

export interface TextInputProps {
  placeholder?: string
  placeholderColor?: string
  maxlength?: number
  readonly?: boolean
  onChange?: (value: string) => void
  onInput?: (value: string) => void
}

type TextInputState = {
}

export class TextInput extends Component<PropsWithChildren<TextInputProps | any>, TextInputState> {
  constructor(props: PropsWithChildren<TextInputProps | any>) {
    super(props);

    this._onChange = this._onChange.bind(this);
    this._onInput = this._onInput.bind(this);

    this.state = {
    };
  }

  _onInput(e: InputEvent) {
    this.props.onInput(e.value);
  }

  _onChange(e: ChangeEvent) {
    this.props.onChange(e.value);
  }

  render() {
    return React.createElement('TextInput', Object.assign({}, this.props, {
      onChange: (e: ChangeEvent) => { this._onChange(e) },
      onInput: (e: InputEvent) => { this._onInput(e) }
    }), this.props.children);
  }
};
