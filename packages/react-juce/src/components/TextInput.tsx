import React, { PropsWithChildren } from 'react';

export interface InputEvent {
  value: string
}

export interface ChangeEvent {
  value: string
}

export interface TextInputProps {
  value?: string,
  placeholder?: string,
  'placeholder-color'?: string,
  maxlength?: number,
  readonly?: boolean,

  onChange?: (e: ChangeEvent) => void,
  onInput?: (e: InputEvent) => void,
}

// //TODO: Remove any once ViewProps typed
export function TextInput(props: PropsWithChildren<TextInputProps | any>) {
  return React.createElement('TextInput', props, props.children);
}
